# Урок 13: Компиляторы C++ — Сравнение, Выбор и Сборка Проектов

## Что такое компилятор?

Компилятор — это программа, которая переводит исходный код C++ в машинный код (исполняемый файл).

```
Исходный код (.cpp) → Препроцессор → Компилятор → Ассемблер → Компоновщик → Программа
```

## Основные компиляторы C++

### 1. GCC (GNU Compiler Collection) — `g++`

**Платформы:** Linux, macOS (через Homebrew), Windows (MinGW/MSYS2)

**Преимущества:**
- Бесплатный и открытый исходный код
- Отличная поддержка стандартов C++ (C++11/14/17/20/23)
- Хорошая оптимизация
- Широко используется в Linux и академической среде
- Лучшая поддержка GCC-специфичных расширений

**Недостатки:**
- Сообщения об ошибках бывают сложными для понимания
- На macOS требует установки через Homebrew

**Установка:**
```bash
# Ubuntu/Debian:
sudo apt install g++

# macOS (через Homebrew):
brew install gcc
# Используется как g++-14 (или текущая версия)

# Windows (MSYS2):
pacman -S mingw-w64-x86_64-gcc
```

**Пример компиляции:**
```bash
g++ -std=c++17 -Wall -Wextra -O2 -o program main.cpp
```

---

### 2. Clang (LLVM) — `clang++`

**Платформы:** macOS (встроен в Xcode), Linux, Windows

**Преимущества:**
- **ЛУЧШИЕ сообщения об ошибках** — понятные, с указанием точного места
- Встроен в macOS через Xcode Command Line Tools
- Быстрая компиляция
- Отличная поддержка современных стандартов C++
- Используется в системах Apple (iOS, macOS приложения)
- Лучше интегрируется с инструментами анализа (sanitizers)

**Недостатки:**
- Иногда чуть медленнее GCC для некоторых задач (оптимизация)

**Установка:**
```bash
# macOS (уже встроен):
xcode-select --install

# Ubuntu/Debian:
sudo apt install clang

# Windows:
# Скачать с https://releases.llvm.org/
```

**Пример компиляции:**
```bash
clang++ -std=c++17 -Wall -Wextra -O2 -o program main.cpp
```

---

### 3. MSVC (Microsoft Visual C++) — `cl`

**Платформы:** Windows (Visual Studio, Visual Studio Build Tools)

**Преимущества:**
- **Лучший выбор для Windows-разработки**
- Отличная интеграция с Visual Studio IDE
- Хорошая поддержка Windows API
- Профессиональные инструменты отладки

**Недостатки:**
- Только Windows
- Платная IDE (хотя есть бесплатная Community Edition)
- Иногда отстаёт от GCC/Clang в поддержке новых стандартов

**Установка:**
- Visual Studio Community (бесплатно): https://visualstudio.microsoft.com/
- Visual Studio Build Tools (только компилятор, без IDE)

**Пример компиляции:**
```cmd
cl /std:c++17 /W4 /O2 /Fe:program.exe main.cpp
```

---

### 4. Intel oneAPI DPC++/C++ Compiler — `icpx`

**Платформы:** Linux, Windows, macOS

**Преимущества:**
- **Лучшая оптимизация для Intel процессоров**
- Поддержка векторизации и параллелизма
- Используется в HPC (High-Performance Computing)

**Недостатки:**
- Платный (есть бесплатная версия для личного использования)
- Ориентирован на специфические задачи

---

## Сравнительная таблица

| Критерий | GCC | Clang | MSVC | Intel |
|----------|-----|-------|------|-------|
| Платформы | Linux, macOS, Win | Все | Windows | Все |
| Сообщения об ошибках | Хорошие | **Отличные** | Хорошие | Средние |
| Скорость компиляции | Средняя | **Быстрая** | Средняя | Медленная |
| Качество оптимизации | **Отличное** | Отличное | Хорошее | **Лучшее для Intel** |
| Поддержка C++20/23 | Отличная | Отличная | Хорошая | Хорошая |
| macOS | Homebrew | **Встроен** | Нет | Homebrew |
| Открытый код | Да | Да | Нет | Нет |
| Бесплатность | Да | Да | Community | Частично |

---

## Что выбрать?

### На macOS:
```
✅ Рекомендуется: Clang (clang++)
   — Встроен, не требует установки
   — Отличные сообщения об ошибках
   — Хорошая оптимизация
   
📌 Альтернатива: GCC через Homebrew
   — Если нужна совместимость с Linux
   — brew install gcc → g++-14
```

### На Linux:
```
✅ Рекомендуется: GCC (g++)
   — Стандартный компилятор Linux
   — Отличная поддержка стандартов
   
📌 Альтернатива: Clang
   — Лучшие сообщения об ошибках
   — Быстрее компилирует
```

### На Windows:
```
✅ Рекомендуется: MSVC (Visual Studio)
   — Лучшая интеграция с Windows
   — Профессиональный инструмент
   
📌 Альтернатива: Clang (clang-cl — совместим с MSVC)
📌 Альтернатива: MinGW GCC (для Linux-подобного окружения)
```

### Для обучения (любая платформа):
```
✅ Используйте тот, что доступен на вашей платформе
   macOS  → clang++
   Linux  → g++
   Windows → cl (MSVC) или g++ (MinGW)
```

---

## Важные флаги компилятора

### Стандарт C++:
```bash
-std=c++11   # C++11
-std=c++14   # C++14
-std=c++17   # C++17 (рекомендуется для обучения)
-std=c++20   # C++20
-std=c++23   # C++23
```

### Предупреждения (ОБЯЗАТЕЛЬНО включайте!):
```bash
-Wall        # Все основные предупреждения
-Wextra      # Дополнительные предупреждения
-Wpedantic   # Строгое следование стандарту
-Werror      # Превратить предупреждения в ошибки (для CI)
```

### Оптимизация:
```bash
-O0    # Без оптимизации (по умолчанию, для отладки)
-O1    # Лёгкая оптимизация
-O2    # Рекомендуемая для продакшена
-O3    # Агрессивная оптимизация
-Os    # Оптимизация по размеру
-Og    # Оптимизация с сохранением отладочной информации
```

### Отладка:
```bash
-g     # Включить отладочную информацию (для gdb/lldb)
-g3    # Максимум отладочной информации
```

### Sanitizers (для поиска ошибок):
```bash
-fsanitize=address      # AddressSanitizer — поиск ошибок памяти
-fsanitize=undefined    # UndefinedBehaviorSanitizer
-fsanitize=thread       # ThreadSanitizer — поиск гонок данных
```

**Пример для разработки:**
```bash
# Debug сборка (разработка):
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined -o program main.cpp

# Release сборка (продакшен):
g++ -std=c++17 -Wall -Wextra -O2 -o program main.cpp
```

---

## Системы сборки: как автоматизировать сборку

### 1. Простой Makefile

Makefile — базовый инструмент автоматизации сборки.

**Создайте файл `Makefile`:**
```makefile
# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
DEBUG_FLAGS = -g -fsanitize=address,undefined
RELEASE_FLAGS = -O2

# Папки
SRC_DIR = lessons
BUILD_DIR = build

# Все .cpp файлы
SOURCES = $(wildcard $(SRC_DIR)/lesson_*.cpp)
# Имена исполняемых файлов (lesson_01, lesson_02, ...)
TARGETS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%, $(SOURCES))

# Правило по умолчанию: собрать всё
all: $(BUILD_DIR) $(TARGETS)

# Создать папку build если не существует
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Правило для компиляции каждого урока
$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) -o $@ $<
	@echo "✅ Собран: $@"

# Debug сборка
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(BUILD_DIR) $(TARGETS)

# Очистить build
clean:
	rm -rf $(BUILD_DIR)

# Запустить конкретный урок: make run LESSON=01
run:
	./$(BUILD_DIR)/lesson_$(LESSON)

.PHONY: all clean debug run
```

**Использование:**
```bash
make          # Собрать все уроки
make debug    # Собрать с отладочными флагами
make clean    # Удалить все собранные файлы
make run LESSON=03  # Запустить урок 3
```

---

### 2. CMake — Кросс-платформенная система сборки

CMake — стандарт индустрии для C++ проектов.

**CMakeLists.txt для уроков:**
```cmake
cmake_minimum_required(VERSION 3.15)
project(cpp_lessons LANGUAGES CXX)

# Стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Строгий стандарт (без GNU расширений)

# Флаги предупреждений
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Debug/Release конфигурации
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(NOT MSVC)
        add_compile_options(-fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    endif()
endif()

# Автоматически найти все уроки
file(GLOB LESSON_SOURCES "lessons/lesson_*.cpp")
foreach(SRC ${LESSON_SOURCES})
    get_filename_component(NAME ${SRC} NAME_WE)
    add_executable(${NAME} ${SRC})
endforeach()
```

**Команды CMake:**
```bash
# Конфигурация:
mkdir build && cd build

# Debug сборка (для разработки):
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# Release сборка (для продакшена):
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

# macOS с Clang:
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release ..

# Сборка конкретного урока:
cmake --build . --target lesson_05

# Параллельная сборка (быстрее):
cmake --build . --parallel 4
```

---

### 3. Shell-скрипт для macOS/Linux (build_all.sh)

**Смотрите файл `build_all.sh` в корне репозитория.**

Использование:
```bash
# Собрать все уроки:
bash build_all.sh

# Собрать конкретный урок:
bash build_all.sh 5

# Собрать и запустить:
bash build_all.sh 5 --run
```

---

### 4. VS Code — настройка для C++

**Файл `.vscode/tasks.json`:**
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Сборка текущего файла",
            "type": "shell",
            "command": "clang++",
            "args": [
                "-std=c++17",
                "-Wall",
                "-Wextra",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

Затем `Cmd+Shift+B` (macOS) или `Ctrl+Shift+B` (Linux/Windows) для сборки.

---

### 5. Ninja — быстрая система сборки

Ninja быстрее Make при больших проектах:

```bash
# Установка:
# macOS: brew install ninja
# Ubuntu: sudo apt install ninja-build

# Использование с CMake:
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
ninja
ninja lesson_05  # Собрать конкретный урок
```

---

## Профессиональные инструменты

### Анализ кода:
```bash
# Clang-Tidy — статический анализатор:
clang-tidy main.cpp -- -std=c++17

# Cppcheck:
cppcheck --enable=all --std=c++17 main.cpp
```

### Отладка:
```bash
# GDB (Linux/macOS с GCC):
g++ -g -o program main.cpp
gdb ./program

# LLDB (macOS с Clang):
clang++ -g -o program main.cpp
lldb ./program
```

### Профилирование:
```bash
# Valgrind (поиск утечек памяти, Linux):
valgrind --leak-check=full ./program

# gprof (профилирование производительности):
g++ -pg -O2 -o program main.cpp
./program
gprof program gmon.out | head -20
```

---

## Советы по выбору

1. **Для обучения**: Используйте тот компилятор, что встроен в вашу систему
2. **Для продакшена**: CMake + GCC/Clang с флагами `-O2 -Wall -Wextra`
3. **Для поиска ошибок**: Добавляйте `-fsanitize=address,undefined`
4. **Всегда компилируйте с**: `-std=c++17 -Wall -Wextra`

```bash
# Минимальная "правильная" команда компиляции:
g++ -std=c++17 -Wall -Wextra -o output input.cpp
```
