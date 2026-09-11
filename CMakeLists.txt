# CMakeLists.txt for Keyboardio Preonic Module

if(CONFIG_KEYBOARDIO_BUTTERFLY_STATUS)
    target_sources_ifdef(CONFIG_KEYBOARDIO_BUTTERFLY_STATUS app PRIVATE src/butterfly_status.c)
    zephyr_include_directories(include)
endif()
