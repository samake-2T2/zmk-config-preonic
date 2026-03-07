# Product Definition: Keyboardio Preonic ZMK Firmware

## 프로젝트 목표
Keyboardio Preonic 키보드를 위한 사용자 정의 ZMK 펌웨어를 구성하고 빌드 환경을 구축합니다.

## 핵심 요구사항
1. **하드웨어 지원**: Keyboardio Preonic (5x12 직교 배열) 지원.
2. **참고 모델**: [BWoodson/keyboardio-preonic-zmk-config](https://github.com/BWoodson/keyboardio-preonic-zmk-config)의 쉴드(Shield) 정의 및 설계를 기반으로 초안 작성.
3. **기능**:
    - 로터리 인코더(Rotary Encoder) 지원.
    - 블루투스 및 유선 연결 지원.
    - 3단계 레이어 구조 (Base, Lower, Raise).
4. **자동화**: GitHub Actions를 통한 펌웨어 자동 빌드 및 배포.

## 대상 하드웨어
- **Keyboard**: Keyboardio Preonic
- **Controller**: Pro Micro 호환 (예: nice!nano v2 권장)
- **Layout**: 5x12 Ortholinear
