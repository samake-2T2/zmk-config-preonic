/*
 * Copyright (c) 2026 Keyboardio Preonic Custom Firmware
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

#include <zmk/activity.h>
#include <zmk/ble.h>
#include <zmk/endpoints.h>
#include <zmk/event_manager.h>
#include <zmk/events/activity_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/events/position_state_changed.h>

#include "butterfly_status.h"

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_NODE_HAS_PROP(DT_CHOSEN(zmk_butterfly), chain_length)
#define BUTTERFLY_NODE DT_CHOSEN(zmk_butterfly)
#elif DT_NODE_HAS_PROP(DT_CHOSEN(zmk_underglow), chain_length)
#define BUTTERFLY_NODE DT_CHOSEN(zmk_underglow)
#elif DT_NODE_EXISTS(DT_NODELABEL(led_strip))
#define BUTTERFLY_NODE DT_NODELABEL(led_strip)
#else
#error "Butterfly LED strip node not found in devicetree"
#endif

#define BUTTERFLY_NUM_LEDS DT_PROP(BUTTERFLY_NODE, chain_length)

#ifndef CONFIG_BUTTERFLY_BOOT_ANIM_MS
#define CONFIG_BUTTERFLY_BOOT_ANIM_MS 1600
#endif

#define BOOT_ANIM_FRAME_MS 20

static const struct device *const strip_dev = DEVICE_DT_GET(BUTTERFLY_NODE);

static struct k_work_delayable butterfly_work;
static int64_t state_change_time = 0;
static int64_t boot_start_time = 0;
static bool boot_anim_done = false;
static bool blink_state = false;
static enum zmk_activity_state current_activity = ZMK_ACTIVITY_ACTIVE;

static inline struct led_rgb make_rgb(uint8_t r, uint8_t g, uint8_t b) {
    return (struct led_rgb){ .r = r, .g = g, .b = b };
}

static void update_leds(struct led_rgb *pixels) {
    if (!device_is_ready(strip_dev)) {
        return;
    }
    (void)led_strip_update_rgb(strip_dev, pixels, BUTTERFLY_NUM_LEDS);
}

static void set_all_off(void) {
    struct led_rgb pixels[BUTTERFLY_NUM_LEDS];
    for (size_t i = 0; i < BUTTERFLY_NUM_LEDS; i++) {
        pixels[i] = make_rgb(0, 0, 0);
    }
    update_leds(pixels);
}

static void butterfly_work_handler(struct k_work *work) {
    if (current_activity == ZMK_ACTIVITY_SLEEP) {
        boot_anim_done = true;
        set_all_off();
        return;
    }

#if CONFIG_BUTTERFLY_BOOT_ANIM_MS > 0
    if (!boot_anim_done) {
        int64_t elapsed = k_uptime_get() - boot_start_time;
        if (elapsed < CONFIG_BUTTERFLY_BOOT_ANIM_MS) {
            int64_t x = (elapsed * 1000) / CONFIG_BUTTERFLY_BOOT_ANIM_MS;
            if (x < 0) {
                x = 0;
            } else if (x > 1000) {
                x = 1000;
            }
            uint32_t bell = (uint32_t)((4 * x * (1000 - x)) / 1000);
            uint32_t eased = (bell * bell) / 1000;
            uint8_t peak = (uint8_t)CONFIG_BUTTERFLY_BRIGHTNESS;
            uint8_t brt = (uint8_t)(((uint32_t)peak * eased) / 1000);
            uint8_t r = brt;
            uint8_t g = (uint8_t)(((uint16_t)brt * 35 + 50) / 100);
            uint8_t b = 0;

            struct led_rgb pixels[BUTTERFLY_NUM_LEDS];
            for (size_t i = 0; i < BUTTERFLY_NUM_LEDS; i++) {
                pixels[i] = make_rgb(r, g, b);
            }
            update_leds(pixels);

            k_work_reschedule(&butterfly_work, K_MSEC(BOOT_ANIM_FRAME_MS));
            return;
        }

        boot_anim_done = true;
        state_change_time = k_uptime_get();
    }
#endif

    struct led_rgb pixels[BUTTERFLY_NUM_LEDS];
    for (size_t i = 0; i < BUTTERFLY_NUM_LEDS; i++) {
        pixels[i] = make_rgb(0, 0, 0);
    }

    enum zmk_transport pref = zmk_endpoint_get_preferred_transport();
    struct zmk_endpoint_instance endpoint = zmk_endpoint_get_selected();

    bool show_ble = false;
#if IS_ENABLED(CONFIG_ZMK_BLE)
    if (pref == ZMK_TRANSPORT_BLE || endpoint.transport == ZMK_TRANSPORT_BLE) {
        show_ble = true;
    }
#endif

#if IS_ENABLED(CONFIG_ZMK_BLE)
    if (show_ble) {
        int prof = zmk_ble_active_profile_index();
        if (prof < 0 || prof >= BUTTERFLY_NUM_LEDS) {
            set_all_off();
            return;
        }

        if (zmk_ble_active_profile_is_connected()) {
            int64_t elapsed = k_uptime_get() - state_change_time;
            bool is_dimmed = (CONFIG_BUTTERFLY_TIMEOUT_MS > 0 && elapsed >= CONFIG_BUTTERFLY_TIMEOUT_MS);
            uint8_t brt = is_dimmed ? (uint8_t)CONFIG_BUTTERFLY_DIM_BRIGHTNESS : (uint8_t)CONFIG_BUTTERFLY_BRIGHTNESS;

            if (brt > 0) {
                uint8_t green_comp = (uint8_t)(((uint16_t)brt * 40) / 100);
                pixels[prof] = make_rgb(0, green_comp, brt);
            }
            update_leds(pixels);

            if (!is_dimmed && CONFIG_BUTTERFLY_TIMEOUT_MS > 0) {
                int64_t remaining = CONFIG_BUTTERFLY_TIMEOUT_MS - elapsed;
                if (remaining > 0) {
                    k_work_reschedule(&butterfly_work, K_MSEC(remaining + 10));
                }
            }
        } else {
            blink_state = !blink_state;
            if (blink_state) {
                uint8_t brt = (uint8_t)CONFIG_BUTTERFLY_BRIGHTNESS;
                uint8_t green_comp = (uint8_t)(((uint16_t)brt * 70) / 100);
                pixels[prof] = make_rgb(0, green_comp, brt);
            } else {
                pixels[prof] = make_rgb(0, 0, 0);
            }
            update_leds(pixels);

            k_work_reschedule(&butterfly_work, K_MSEC(CONFIG_BUTTERFLY_BLINK_MS));
        }
        return;
    }
#endif

#if IS_ENABLED(CONFIG_ZMK_USB)
    if (endpoint.transport == ZMK_TRANSPORT_USB || pref == ZMK_TRANSPORT_USB) {
        int64_t elapsed = k_uptime_get() - state_change_time;
        bool is_dimmed = (CONFIG_BUTTERFLY_TIMEOUT_MS > 0 && elapsed >= CONFIG_BUTTERFLY_TIMEOUT_MS);
        uint8_t brt = is_dimmed ? (uint8_t)CONFIG_BUTTERFLY_DIM_BRIGHTNESS : (uint8_t)CONFIG_BUTTERFLY_BRIGHTNESS;

        for (size_t i = 0; i < BUTTERFLY_NUM_LEDS; i++) {
            pixels[i] = make_rgb(0, brt, 0);
        }
        update_leds(pixels);

        if (!is_dimmed && CONFIG_BUTTERFLY_TIMEOUT_MS > 0) {
            int64_t remaining = CONFIG_BUTTERFLY_TIMEOUT_MS - elapsed;
            if (remaining > 0) {
                k_work_reschedule(&butterfly_work, K_MSEC(remaining + 10));
            }
        }
        return;
    }
#endif

    set_all_off();
}

void butterfly_status_refresh(void) {
    state_change_time = k_uptime_get();
    blink_state = false;
    k_work_reschedule(&butterfly_work, K_NO_WAIT);
}

static int butterfly_event_listener(const zmk_event_t *eh) {
    struct zmk_activity_state_changed *act_ev = as_zmk_activity_state_changed(eh);
    if (act_ev != NULL) {
        current_activity = act_ev->state;
        if (current_activity == ZMK_ACTIVITY_SLEEP) {
            k_work_cancel_delayable(&butterfly_work);
            set_all_off();
            return 0;
        }
    }

    const struct zmk_position_state_changed *pos_ev = as_zmk_position_state_changed(eh);
    if (pos_ev != NULL) {
        if (!pos_ev->state) {
            return 0;
        }
        boot_anim_done = true;
    }

    butterfly_status_refresh();
    return 0;
}

ZMK_LISTENER(butterfly_status, butterfly_event_listener);
#if IS_ENABLED(CONFIG_ZMK_BLE)
ZMK_SUBSCRIPTION(butterfly_status, zmk_ble_active_profile_changed);
#endif
#if IS_ENABLED(CONFIG_ZMK_USB) || IS_ENABLED(CONFIG_ZMK_BLE)
ZMK_SUBSCRIPTION(butterfly_status, zmk_endpoint_changed);
#endif
#if IS_ENABLED(CONFIG_ZMK_USB)
ZMK_SUBSCRIPTION(butterfly_status, zmk_usb_conn_state_changed);
#endif
ZMK_SUBSCRIPTION(butterfly_status, zmk_position_state_changed);
ZMK_SUBSCRIPTION(butterfly_status, zmk_activity_state_changed);

static int butterfly_init(void) {
    k_work_init_delayable(&butterfly_work, butterfly_work_handler);
#if CONFIG_BUTTERFLY_BOOT_ANIM_MS > 0
    boot_anim_done = false;
    boot_start_time = k_uptime_get();
#else
    boot_anim_done = true;
#endif
    butterfly_status_refresh();
    return 0;
}

SYS_INIT(butterfly_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
