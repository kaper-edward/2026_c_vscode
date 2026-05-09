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
- **빌드 + 실행:** CMake Tools 하단 바 ▶ 버튼 또는 `F5` (디버그) / `Ctrl+F5` (디버그 없이 실행)
- **실행 타겟 선택:** 하단 상태바의 `[lab_q01]` 클릭

### `F5` / `Ctrl+F5` 사용 전 두 곳을 반드시 확인

이 프로젝트의 `launch.json` 구성 `Debug (cmake target)`은 실행할 바이너리를
CMake Tools가 알려주는 **launch target**(`${command:cmake.getLaunchTargetPath}`)으로
찾습니다. 따라서 `F5`(Start Debugging) / `Ctrl+F5`(Run Without Debugging)을
누르기 전에 아래 두 가지를 함께 맞춰야 원하는 lab이 실행됩니다.

1. **Run and Debug 뷰 (좌측 ▶🐞 아이콘)** → 상단 구성 드롭다운에서
   `Debug (cmake target)` 가 선택돼 있는지 확인합니다.
   (VS Code의 `F5` / `Ctrl+F5` 는 이 드롭다운에 선택된 launch.json 구성을 사용합니다.)
2. **하단 상태바의 CMake 실행 타겟** → 클릭해서 실행하고 싶은
   lab (예: `[lab_q01]`)이 선택돼 있는지 확인합니다.
   (`launch.json` 의 `program`이 이 값을 참조합니다.)

> 참고: CMake Tools는 자체 단축키도 제공합니다.
> `Shift+F5` = `CMake: Debug`, `Shift+Ctrl+F5` = `CMake: Run Without Debugging`.
> 이 단축키들은 `launch.json` 없이 상태바의 launch target만 보고 바로 실행합니다.

### 단축키 한눈에 보기

| 의도 | 권장 단축키 | 실제 경로 | 빌드 자동? |
|------|-----------|----------|-----------|
| 디버그 (중단점, step) | **`F5`** | launch.json `Debug (cmake target)` → `cppdbg` → GDB/LLDB | ✅ `preLaunchTask` 가 빌드 |
| 그냥 실행 (디버그 없이) | **`Shift+Ctrl+F5`** | CMake Tools `cmake.launchTarget` → 통합 터미널에서 바이너리 직접 실행 | ✅ `cmake.buildBeforeRun: true` 가 빌드 |

> 핵심: **디버깅은 `F5`, 실행은 `Shift+Ctrl+F5`.** `Ctrl+F5`도 대부분 동작하지만
> OS 별 차이가 있어 아래 보충 설명을 한 번 읽어보길 권합니다.

### `Ctrl+F5` 동작에 대한 보충 설명 (선택 읽기)

VS Code 표준에서 `Ctrl+F5`는 *Run Without Debugging* 으로, **선택된 launch.json
구성을 그대로 디버그 어댑터에 넘기되 `noDebug=true` 플래그만 추가**해서 실행을
위임합니다. 즉 `Ctrl+F5`도 결국 `launch.json` 경로(이 프로젝트의 경우 `cppdbg`)를
탑니다. 진짜 "디버거 없이" 실행되는지는 어댑터가 그 플래그를 존중하느냐에 따라
달라집니다.

**Windows (MSYS2 UCRT64 + GDB) / macOS (LLDB)** — 일상 사용에 문제가 없습니다.
프로그램이 정상 종료되면 디버그 세션도 함께 정리되어 다음 실행이 바로 가능합니다.
**대부분의 학생(Windows/Mac)은 이 섹션을 더 읽지 않아도 됩니다.**

**Linux (GDB) 환경의 알려진 이슈** — `cppdbg` (Microsoft C/C++ 확장의 MIEngine)가
DAP `noDebug=true` 플래그를 무시하고 GDB를 그대로 띄우는 한계가 있습니다
([cpptools #1201](https://github.com/microsoft/vscode-cpptools/issues/1201),
[#5680](https://github.com/microsoft/vscode-cpptools/issues/5680),
[vscode #115600](https://github.com/microsoft/vscode/issues/115600)).
이 때문에 다음 증상이 나타날 수 있습니다.

1. `Ctrl+F5`로 실행한 프로그램이 정상 종료되었는데도 **디버그 툴바
   (Continue / Step / Stop 버튼)** 가 사라지지 않음.
2. 다시 `Ctrl+F5`를 누르면 *"이미 디버그 세션이 활성 상태입니다"* 경고가 뜸.

특히 이 프로젝트 기본 설정인 `console: integratedTerminal` 조합에서 자주
발생합니다. cpptools가 통합 터미널 입출력을 wrapper 스크립트로 우회시키는데,
GDB가 그 파이프 닫힘을 기다리며 종료를 못 하는 케이스가 있기 때문입니다.

**Linux 학생을 위한 권장 사항:**

1. **단순 실행은 `Shift+Ctrl+F5`를 사용하세요.** `cmake.launchTarget` 명령은
   `launch.json` / GDB를 완전히 우회하고 바이너리를 통합 터미널에서 그대로
   실행하므로 잔존 세션이 발생하지 않습니다.
2. **그래도 `Ctrl+F5`를 쓰고 싶다면** — 사용자 `keybindings.json`
   (`Ctrl+Shift+P` → *Preferences: Open Keyboard Shortcuts (JSON)*)에 다음을
   추가해 `Ctrl+F5`를 CMake Tools 실행 명령으로 재바인딩하세요.

   ```jsonc
   {
       "key": "ctrl+f5",
       "command": "cmake.launchTarget",
       "when": "cmake:enableFullFeatureSet"
   }
   ```

3. **이미 디버그 세션이 남아 있을 때** — 디버그 툴바의 **빨간 정사각형(■) 정지
   버튼**을 눌러 세션을 명시적으로 종료한 뒤 다시 실행하면 됩니다.

> 요약: **디버깅은 `F5`, 실행은 `Shift+Ctrl+F5`.** Windows/Mac 학생은
> `Ctrl+F5`도 그냥 써도 무방하고, Linux 학생은 위 권장 사항을 따르면 가장 깔끔합니다.

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
