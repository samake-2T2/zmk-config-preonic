# Tech Stack: ZMK Firmware Configuration

## Firmware Framework
- **ZMK Firmware**: 오픈 소스 무선 키보드 펌웨어.
- **Zephyr RTOS**: ZMK의 기반이 되는 실시간 운영체제.

## Build & Deployment
- **GitHub Actions**: 펌웨어 빌드 자동화 파이프라인.
- **Docker**: (로컬 빌드 시) ZMK 빌드 환경 컨테이너.

## Hardware Configuration (DTS/Kconfig)
- **Devicetree (.overlay)**: 하드웨어 핀 매핑 및 매트릭스 정의.
- **Kconfig (.conf)**: 기능 활성화 및 시스템 설정.
- **Keymap (.keymap)**: 레이어 및 키 동작 정의.

## Version Control
- **Git**: 버전 관리 및 변경 이력 추적.
- **GitHub**: 원격 저장소 및 빌드 결과물 저장.
