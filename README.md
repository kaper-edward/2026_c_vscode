# C11 Course Starter — VS Code + MSYS2 UCRT64 (Windows)

C11 실습 프로젝트 템플릿입니다. CMake + Ninja 빌드 시스템을 사용하며 VS Code에서 바로 빌드·디버그가 가능합니다.

---

## 실행 환경 설치 (Windows)

### 1. MSYS2 설치

1. [https://www.msys2.org](https://www.msys2.org) 에서 설치 파일 다운로드 후 실행
2. 기본 경로 `C:\msys64` 유지 (변경하지 않도록 합니다)
3. 설치 완료 후 **MSYS2 UCRT64** 터미널을 실행합니다

### 2. 필수 패키지 설치

**MSYS2 UCRT64 터미널**에서 아래 명령을 순서대로 실행합니다.

```bash
# 패키지 데이터베이스 업데이트
pacman -Syu

# 터미널이 재시작되면 다시 열고 계속 업데이트
pacman -Su

# GCC (C 컴파일러)
pacman -S mingw-w64-ucrt-x86_64-gcc

# CMake
pacman -S mingw-w64-ucrt-x86_64-cmake

# Ninja (빌드 시스템)
pacman -S mingw-w64-ucrt-x86_64-ninja

# GDB (디버거)
pacman -S mingw-w64-ucrt-x86_64-gdb
```

설치 확인:

```bash
gcc --version
cmake --version
ninja --version
gdb --version
```

### 3. Windows PATH 설정

`C:\msys64\ucrt64\bin` 을 Windows 시스템 환경 변수 `PATH`에 추가합니다.

**방법:**
1. `Win + R` → `sysdm.cpl` 입력 → 엔터
2. **고급** 탭 → **환경 변수** 클릭
3. **시스템 변수** 목록에서 `Path` 선택 → **편집**
4. **새로 만들기** → `C:\msys64\ucrt64\bin` 입력 → 확인
5. 모든 창 확인 후 **VS Code 재시작**

> PATH 설정 후 CMD 또는 PowerShell에서도 `gcc`, `cmake`, `ninja` 명령을 바로 사용할 수 있습니다.

---

## VS Code 확장 설치

VS Code에서 아래 확장을 설치합니다.

| 확장 이름 | ID |
|----------|----|
| C/C++ | `ms-vscode.cpptools` |
| CMake Tools | `ms-vscode.cmake-tools` |

---

## 프로젝트 클론 및 빌드

```bash
git clone https://github.com/edward-leafmill/2026_c_vscode.git
cd 2026_c_vscode
```

VS Code에서 폴더 열기:

```bash
code .
```

VS Code가 열리면 CMake Tools가 자동으로 configure를 실행합니다.

- **빌드 (전체):** `Ctrl+Shift+B` → `CMake: build all`
- **빌드 + 실행:** CMake Tools 하단 바 ▶ 버튼 또는 `F5` (디버그)
- **실행 타겟 선택:** 하단 상태바의 `[lab_q01]` 클릭

---

## 프로젝트 구조

```
2026_c_vscode/
├── CMakeLists.txt          # 최상위 빌드 설정 (enable_course_c11 함수 포함)
├── cmake/
│   └── kill_if_running.cmake   # 빌드 전 실행 중인 exe 자동 종료 (Windows)
├── .vscode/
│   ├── settings.json       # CMake Tools 설정 (Ninja, UCRT64 경로)
│   ├── tasks.json          # 빌드 태스크 (MSYS2 bash 쉘)
│   └── launch.json         # GDB 디버그 설정
└── labs/
    ├── CMakeLists.txt      # lab 자동 등록
    ├── q01/                # 실습 01: 원의 넓이
    ├── q02/                # 실습 02: 팩토리얼
    └── q03/                # 실습 03: 계산기 (다중 파일)
```

---

## 새 lab 추가 방법

```
labs/
└── q04/
    ├── CMakeLists.txt   ← 기존 lab의 CMakeLists.txt를 그대로 복사
    └── main.c
```

`CMakeLists.txt` 내용은 모든 lab 동일합니다. 폴더 이름이 곧 타겟 이름이 됩니다 (`lab_q04`).

---

## 빌드 환경 요약

| 항목 | 값 |
|------|----|
| 컴파일러 | GCC 15.x (MSYS2 UCRT64) |
| C 표준 | C11 |
| 빌드 시스템 | CMake 4.x + Ninja |
| 디버거 | GDB (MSYS2 UCRT64) |
| 경고 옵션 | `-Wall -Wextra -Wpedantic` |
| 컴파일러 경로 | `C:/msys64/ucrt64/bin/gcc.exe` |
| GDB 경로 | `C:/msys64/ucrt64/bin/gdb.exe` |
