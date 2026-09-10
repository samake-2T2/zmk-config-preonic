# Keyboardio Preonic - ZMK Firmware Configuration

<p align="center">
  <a href="#english">English</a> | <a href="#한국어">한국어</a>
</p>

---

<a name="english"></a>
## English

Custom ZMK firmware configuration for the **Keyboardio Preonic**, a 5×12 ortholinear mechanical keyboard featuring a rotary encoder and two auxiliary top-row keys.

### ✨ Features

* **5×12 Ortholinear (MIT Layout)**: 62 keys total (including 2 top buttons, 1 rotary encoder push switch, and a centered 2U spacebar).
* **Rotary Encoder (EC11)**: Smooth volume control (`Volume Up / Down`) with click-to-mute (`C_MUTE`).
* **Enhanced Wireless Connection**: Bluetooth Low Energy (BLE) with 5 profile slots and **+8 dBm** transmit power for maximum stability.
* **Low-Latency Debouncing**: Optimized debouncing (1 ms press / 5 ms release) for rapid response and debounce error prevention.
* **Full NKRO**: N-Key Rollover enabled for simultaneous keypress accuracy.
* **RGB Underglow**: Butterfly logo illuminated on startup with a signature cyan breathing effect (`HSV: 195, 100, 100`).
* **Mouse Emulation (ZMK Pointing)**: Integrated mouse cursor movement, clicking, and scrolling on the Raise layer.
* **Tri-Layer Support**: Simultaneously holding `Lower` and `Raise` automatically activates the `Function` layer.
* **GUI Configurator Compatibility**:
  * **Keymap Editor**: Pre-configured layout metadata (`config/keyboardio_preonic.json` & `config/info.json`) with `row` and `col` properties for clean devicetree formatting.
  * **ZMK Studio**: Real-time keymap and layer adjustments over USB via ZMK Studio.

---

### 🗺️ Layer Map

#### 1. Base Layer
* **Top Row (Right)**: `PrintScreen` | `Fn (L_FN)` | `Knob Click (Mute)`
* **Main Grid**: Standard Preonic ortholinear alpha layout with 2U Spacebar.
* **Thumbs**: `LCTRL`, `LGUI`, `LALT`, `RALT`, `Lower`, `Space`, `Raise`, Arrow keys (`Left`, `Down`, `Up`, `Right`).

#### 2. Lower Layer (Numpad & Navigation)
* **Right Hand**: Dedicated 10-key numeric keypad (`KP_N0` ~ `KP_N9`, `.`, `Enter`).
* **Left Hand**: `F1` ~ `F11`, `Home`, `End`, `Page Up`, `Page Down`, `Insert`, `Delete`.
* **Bottom Row**: Cyan breathing effect toggle & RGB On/Off toggle.

#### 3. Raise Layer (Symbols & Mouse Keys)
* **Symbols**: Brackets, braces, parentheses, mathematical operators.
* **Mouse Emulation**: Cursor movement (`MOVE_UP`, `MOVE_DOWN`, etc.), buttons (`LCLK`, `RCLK`, `MCLK`, `MB4`, `MB5`), and wheel scrolling (`SCRL_UP`, `SCRL_DOWN`, etc.).
* **Bottom Row**: RGB controls and breathing toggle.

#### 4. Function Layer (Official Keyboardio Preonic Layout)
* **Number Row**:
  * `Grave` position: `&out OUT_TOG` (Toggle between USB and BLE output)
  * `1` ~ `5`: `&bt BT_SEL 0` ~ `&bt BT_SEL 4` (Select Bluetooth profiles 1 to 5)
* **Bottom Row**:
  * `LCTRL` position: `&bootloader` (Enter DFU bootloader mode)
  * `Lower` position: `&studio_unlock` (Unlock ZMK Studio)
  * `Right` position: `&bt BT_CLR` (Clear current Bluetooth bonding)

---

### 📥 Flashing Firmware

1. **Build**: Every push to `master` triggers a GitHub Actions build producing a firmware `.uf2` artifact.
2. **Enter Bootloader Mode**:
   * **Via Keyboard**: Hold `Fn` and tap the bottom-left key (`LCTRL` position).
   * **Via Hardware**: Double-press the physical reset button on the board.
3. **Flash**: Drag and drop the downloaded `keyboardio_preonic__zmk.uf2` into the mounted USB mass-storage drive (`PREONIC`). The device will reboot automatically once finished.

---

### 🛠️ Web GUI Customization

* **[Keymap Editor](https://nickcoutsos.github.io/keymap-editor/)**: Connect your GitHub repository to visually customize bindings, combos, and rotary encoder actions.
* **[ZMK Studio](https://zmk.dev/docs/features/studio)**: Connect via WebUSB for instant on-the-fly key reassignment without rebuilding firmware.

---
---

<a name="한국어"></a>
## 한국어

**Keyboardio Preonic** 기계식 키보드를 위한 사용자 정의 ZMK 펌웨어 설정 저장소입니다. 5×12 직교(Ortholinear) 배열과 로터리 인코더, 상단 보조 키를 완벽하게 지원합니다.

### ✨ 주요 기능

* **5×12 직교 배열 (MIT Layout)**: 중앙 2U 스페이스바, 상단 2개 보조 키 및 로터리 인코더 푸시 스위치 포함 총 62개 키 지원.
* **로터리 인코더 (EC11)**: 부드러운 볼륨 조절(`Volume Up / Down`) 및 클릭 시 음소거(`C_MUTE`) 동작.
* **안정적인 무선 연결**: 블루투스 저전력(BLE) 5개 프로필 슬롯 및 **+8 dBm 최대 송신 출력** 설정으로 연결 끊김 최소화.
* **초저지연 디바운스**: 1ms 누름 / 5ms 릴리즈 설정으로 키 입력 반응성 극대화 및 채터링 방지.
* **NKRO 완벽 지원**: 무한 동시 입력(N-Key Rollover) 지원.
* **나비 로고 RGB 언더글로우**: 부팅 시 시그니처 스카이블루 숨쉬기(Cyan Breathing, `HSV: 195, 100, 100`) 효과 자동 점등.
* **마우스 에뮬레이션 (ZMK Pointing)**: Raise 레이어에서 마우스 커서 이동, 클릭, 휠 스크롤 지원.
* **트라이 레이어(Tri-Layer)**: `Lower` 키와 `Raise` 키를 동시에 누르면 자동으로 `Function` 레이어로 전환.
* **웹 GUI 도구 완벽 호환**:
  * **Keymap Editor**: 전용 레이아웃 메타데이터(`row`, `col` 포함)를 완비하여 소스코드 가독성 경고 해결 및 깔끔한 코드 정렬 지원.
  * **ZMK Studio**: 펌웨어 재빌드 없이 실시간으로 키 매핑을 수정할 수 있는 ZMK Studio 지원.

---

### 🗺️ 레이어 구성

#### 1. 기본 레이어 (Base Layer)
* **상단 우측 3키**: `PrintScreen` (화면 캡처) | `Fn (L_FN)` (펑션 레이어 진입) | `노브 클릭` (음소거)
* **알파벳 열**: 표준 Preonic 직교 영문 자판 및 중앙 2U 스페이스바.
* **하단 열**: `LCTRL`, `LGUI`, `LALT`, `RALT`, `Lower`, `Space`, `Raise`, 방향키 (`Left`, `Down`, `Up`, `Right`).

#### 2. 로워 레이어 (Lower Layer - 숫자 패드 & 내비게이션)
* **우측 손**: 텐키리스 숫자 키패드(`KP_N0` ~ `KP_N9`, `.`, `Enter`).
* **좌측 손**: `F1` ~ `F11`, `Home`, `End`, `Page Up`, `Page Down`, `Insert`, `Delete`.
* **하단 열**: 하늘색 숨쉬기 효과 활성화 및 RGB On/Off 토글.

#### 3. 레이즈 레이어 (Raise Layer - 특수기호 & 마우스)
* **특수 기호**: 괄호(`[]`, `{}`, `()`), 연산 기호 등 프로그래밍에 유용한 기호 배치.
* **마우스 제어**: 커서 이동(`MOVE_UP`, `MOVE_DOWN` 등), 클릭(`좌클릭`, `우클릭`, `휠클릭`, `앞/뒤로가기`), 휠 스크롤.
* **하단 열**: RGB 효과 제어 및 조작.

#### 4. 펑션 레이어 (Function Layer - 공식 순정 키맵 규격)
* **숫자 행**:
  * `Grave` 자리: **`&out OUT_TOG`** (USB 유선 / 블루투스 무선 출력 모드 전환)
  * `1 ~ 5` 자리: **`&bt BT_SEL 0 ~ 4`** (블루투스 기기 슬롯 1번 ~ 5번 선택)
* **하단 행**:
  * `LCTRL` 자리: **`&bootloader`** (USB 외장 드라이브 부트로더 모드 진입)
  * `Lower` 자리: **`&studio_unlock`** (ZMK Studio 잠금 해제)
  * `Right` 자리: **`&bt BT_CLR`** (현재 연결된 블루투스 페어링 정보 삭제)

---

### 📥 펌웨어 빌드 및 설치 방법

1. **자동 빌드**: `master` 브랜치에 코드를 푸시하면 GitHub Actions 파이프라인이 자동으로 펌웨어를 빌드하여 릴리스/아티팩트로 생성합니다.
2. **부트로더 진입 방법**:
   * **키 조합**: `Fn` 키를 누른 상태에서 하단 가장 왼쪽 키(`LCTRL` 자리)를 입력합니다.
   * **물리 버튼**: 키보드 기판의 리셋 버튼을 빠르게 2회 클릭합니다.
3. **설치**: PC에 `PREONIC`이라는 이름의 외장 드라이브가 인식되면, 다운로드한 `keyboardio_preonic__zmk.uf2` 파일을 드래그 앤 드롭(또는 복사)합니다. 복사가 완료되면 자동으로 키보드가 재부팅되며 새 펌웨어가 적용됩니다.

---

### 🛠️ 웹 GUI 설정 도구 활용

* **[Keymap Editor](https://nickcoutsos.github.io/keymap-editor/)**: GitHub 계정을 연결하여 웹 브라우저에서 직관적으로 키맵, 콤보, 인코더 바인딩을 수정할 수 있습니다.
* **[ZMK Studio](https://zmk.dev/docs/features/studio)**: WebUSB를 지원하는 브라우저(Chrome, Edge 등)에서 키보드를 연결하면 펌웨어 플래시 없이 즉시 키를 바꿀 수 있습니다.

---

### 📂 저장소 구조

```text
├── .github/workflows/build.yml   # GitHub Actions 빌드 자동화 워크플로우
├── boards/keyboardio/           # Keyboardio Preonic 보드 및 DTS 정의
├── config/
│   ├── keyboardio_preonic.keymap # 4단계 레이어 키 매핑 정의
│   ├── keyboardio_preonic.conf   # 블루투스, RGB, NKRO, 마우스 설정
│   ├── keyboardio_preonic.json   # Keymap Editor용 레이아웃 메타데이터
│   ├── info.json                 # GUI 도구 호환용 표준 메타데이터
│   └── west.yml                  # ZMK 빌드 매니페스트
└── build.yaml                    # 빌드 타겟 보드 및 스니펫 지정
```
