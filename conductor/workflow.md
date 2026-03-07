# Workflow: ZMK Configuration Process

## Git 전략
- **Main Branch**: 안정화된 설정 및 펌웨어 릴리스.
- **Feature Branches**: 새로운 키맵 실험 또는 기능 추가 시 사용.
- **Commit Convention**: 한글 또는 영문으로 명확한 작업 내용 기술.

## 개발 프로세스
1. **초기화**: 로컬 Git 저장소 및 Conductor 설계 파일 작성.
2. **레퍼런스 복제**: 참고 레포지토리의 핵심 쉴드 파일 및 설정 구조 이식.
3. **환경 설정**: `build.yaml` 및 GitHub Actions 워크플로우 설정.
4. **커스터마이징**: 사용자 취향에 맞는 키맵 수정.
5. **검증**: 빌드 성공 여부 확인 및 실제 하드웨어 플래싱 (사용자 수행).
