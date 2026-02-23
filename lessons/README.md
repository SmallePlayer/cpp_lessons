# Уроки C++ (для Python-разработчиков)

Курс из 12 уроков по C++, основанный на материалах [learncpp.com](https://www.learncpp.com/).
Каждый урок содержит подробную теорию, сравнение с Python и практические задания.

## Как компилировать и запускать

```bash
# Компиляция одного урока:
g++ -std=c++17 -Wall -Wextra -o lesson_01 lessons/lesson_01.cpp

# Запуск:
./lesson_01        # Linux/macOS
lesson_01.exe      # Windows

# Или одной командой:
g++ -std=c++17 -Wall -Wextra -o lesson_01 lessons/lesson_01.cpp && ./lesson_01
```

### Флаги компилятора:
- `-std=c++17` — использовать стандарт C++17
- `-Wall` — включить все основные предупреждения
- `-Wextra` — включить дополнительные предупреждения
- `-o имя` — имя выходного файла

## Компиляция на macOS

На macOS можно использовать **Clang** (входит в состав Xcode Command Line Tools)
или **GCC** через Homebrew.

### Установка инструментов на macOS

```bash
# Вариант 1: Xcode Command Line Tools (рекомендуется)
xcode-select --install

# Вариант 2: GCC через Homebrew
brew install gcc
# После установки: g++-14 вместо g++
```

### Компиляция с Clang (macOS по умолчанию)

```bash
# Компиляция одного урока:
clang++ -std=c++17 -Wall -Wextra -o lesson_01 lessons/lesson_01.cpp

# Запуск:
./lesson_01
```

### Компиляция через CMake на macOS

```bash
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=clang++ ..
cmake --build .
```

### Shell-скрипт для macOS/Linux

```bash
# Сборка всех уроков (build_all.sh):
bash build_all.sh

# Сборка одного урока:
bash build_all.sh 3
```

## Список уроков

| # | Файл | Тема |
|---|------|------|
| 1 | `lesson_01.cpp` | Введение в C++, Hello World, cout, комментарии, типы |
| 2 | `lesson_02.cpp` | Переменные, типы данных, операторы, const, auto |
| 3 | `lesson_03.cpp` | Строки (std::string, string_view, методы) |
| 4 | `lesson_04.cpp` | Условия (if/else, switch, тернарный оператор) |
| 5 | `lesson_05.cpp` | Циклы (for, while, do-while, range-based for) |
| 6 | `lesson_06.cpp` | Функции, лямбды, перегрузка, рекурсия |
| 7 | `lesson_07.cpp` | Контейнеры STL (vector, map, set, array, алгоритмы) |
| 8 | `lesson_08.cpp` | Указатели, ссылки, умные указатели (unique_ptr, shared_ptr) |
| 9 | `lesson_09.cpp` | Структуры и Классы (ООП, конструкторы, перегрузка операторов) |
| 10 | `lesson_10.cpp` | Наследование и Полиморфизм (virtual, override, абстракции) |
| 11 | `lesson_11.cpp` | Обработка ошибок (try/catch, exceptions, optional, RAII) |
| 12 | `lesson_12.cpp` | Шаблоны и Современный C++ (templates, constexpr, move) |
| 13 | `lesson_13_compilers.md` | Компиляторы: сравнение, выбор, сборка проектов |
| 14 | `lesson_14_boost_intro.cpp` | Boost: введение, установка, filesystem |
| 15 | `lesson_15_boost_asio.cpp` | Boost.Asio: асинхронный ввод-вывод |
| 16 | `lesson_16_boost_regex_json.cpp` | Boost.Regex и сериализация |

## Компиляция всех уроков (CMake)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Или используйте скрипт `build_all.sh` (Linux/macOS) или `build_all.ps1` (Windows PowerShell).

## Порядок изучения

Рекомендуется изучать уроки последовательно (1 → 12), затем дополнительные уроки.
Каждый урок опирается на знания из предыдущих.
