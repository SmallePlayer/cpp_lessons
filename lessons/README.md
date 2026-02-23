# роки C++ (для Python-разработчиков)

урс из 12 уроков по C++, основанный на материалах [learncpp.com](https://www.learncpp.com/).
аждый урок содержит подробную теорию, сравнение с Python и практические задания.

## ак компилировать и запускать

```bash
# омпиляция одного урока:
g++ -std=c++17 -Wall -Wextra -o lesson_01 lessons/lesson_01.cpp

# апуск:
./lesson_01        # Linux/macOS
lesson_01.exe      # Windows

# ли одной командой:
g++ -std=c++17 -Wall -Wextra -o lesson_01 lessons/lesson_01.cpp && ./lesson_01
```

### лаги компилятора:
- `-std=c++17` — использовать стандарт C++17
- `-Wall` — включить все основные предупреждения
- `-Wextra` — включить дополнительные предупреждения
- `-o имя` — имя выходного файла

## Список уроков

| # | айл | Тема |
|---|------|------|
| 1 | `lesson_01.cpp` | ведение в C++, Hello World, cout, комментарии, типы |
| 2 | `lesson_02.cpp` | еременные, типы данных, операторы, const, auto |
| 3 | `lesson_03.cpp` | Строки (std::string, string_view, методы) |
| 4 | `lesson_04.cpp` | словия (if/else, switch, тернарный оператор) |
| 5 | `lesson_05.cpp` | иклы (for, while, do-while, range-based for) |
| 6 | `lesson_06.cpp` | ункции, лямбды, перегрузка, рекурсия |
| 7 | `lesson_07.cpp` | онтейнеры STL (vector, map, set, array, алгоритмы) |
| 8 | `lesson_08.cpp` | казатели, ссылки, умные указатели (unique_ptr, shared_ptr) |
| 9 | `lesson_09.cpp` | Структуры и лассы (, конструкторы, перегрузка операторов) |
| 10 | `lesson_10.cpp` | аследование и олиморфизм (virtual, override, абстракции) |
| 11 | `lesson_11.cpp` | бработка ошибок (try/catch, exceptions, optional, RAII) |
| 12 | `lesson_12.cpp` | Шаблоны и Современный C++ (templates, constexpr, move) |

## омпиляция всех уроков (CMake)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

ли используйте скрипт `build_all.ps1` (Windows PowerShell).

## орядок изучения

екомендуется изучать уроки последовательно (1 → 12).
аждый урок опирается на знания из предыдущих.