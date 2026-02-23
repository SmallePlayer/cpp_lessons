// =============================================================================
// Урок 14: Boost — Введение, установка, Boost.Filesystem
// =============================================================================
// Boost — это коллекция высококачественных библиотек для C++.
// Многие функции Boost стали частью стандарта C++ (std::shared_ptr,
// std::optional, std::filesystem, std::regex и др. пришли из Boost).
//
// Темы:
//   - Что такое Boost и зачем он нужен
//   - Установка Boost на разных платформах
//   - Boost.Filesystem — работа с файловой системой
//   - Boost.Lexical_cast — безопасное приведение типов
//   - Boost.String Algorithms — алгоритмы для строк
//   - Boost.Optional — необязательные значения
//   - Boost.Date_Time — работа с датами и временем
//
// УСТАНОВКА BOOST:
//
//   macOS (Homebrew):
//     brew install boost
//     Компиляция: clang++ -std=c++17 lesson_14.cpp -lboost_filesystem -lboost_system
//
//   Ubuntu/Debian:
//     sudo apt install libboost-all-dev
//     Компиляция: g++ -std=c++17 lesson_14.cpp -lboost_filesystem -lboost_system
//
//   Windows (vcpkg):
//     vcpkg install boost
//
//   Через CMake:
//     find_package(Boost REQUIRED COMPONENTS filesystem system)
//     target_link_libraries(myapp Boost::filesystem Boost::system)
//
// ПРИМЕЧАНИЕ: В C++17 std::filesystem заменяет Boost.Filesystem для
// новых проектов. Но Boost.Filesystem поддерживает и старые стандарты.
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <optional>
#include <filesystem>
#include <cmath>

// Boost заголовочные файлы (требуют установки Boost):
// #include <boost/filesystem.hpp>
// #include <boost/lexical_cast.hpp>
// #include <boost/algorithm/string.hpp>
// #include <boost/optional.hpp>
// #include <boost/date_time/posix_time/posix_time.hpp>

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 1: Что такое Boost?
// ─────────────────────────────────────────────────────────────────────────────
//
// Boost — это набор из 160+ портируемых библиотек для C++.
// Сайт: https://www.boost.org/
//
// Ключевые особенности:
// 1. КАЧЕСТВО — все библиотеки проходят строгое рецензирование
// 2. ПЕРЕНОСИМОСТЬ — работает на всех основных платформах
// 3. СОВМЕСТИМОСТЬ — поддерживает разные стандарты C++
// 4. ВЛИЯНИЕ НА СТАНДАРТ — многие библиотеки попали в C++11/14/17/20
//
// Что пришло из Boost в стандарт C++:
//   Boost → C++11: shared_ptr, weak_ptr, unique_ptr, regex, unordered_map
//   Boost → C++17: filesystem, optional, any, variant, string_view
//   Boost → C++20: span, bit operations
//
// Категории библиотек Boost:
//   • Строки и текст: String Algorithms, Regex, Tokenizer
//   • Контейнеры: Container, MultiArray, Bimap
//   • Функциональное программирование: Function, Bind, Lambda
//   • Математика: Math, Multiprecision, Accumulators
//   • Метапрограммирование: MPL, TypeTraits, Hana
//   • Ввод-вывод: Filesystem, Serialization, Asio
//   • Многопоточность: Thread, Atomic, Fiber
//   • Сеть: Asio (сетевое программирование)
//   • Парсинг: Spirit, Program_options
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 2: Boost.Lexical_cast
// ─────────────────────────────────────────────────────────────────────────────
//
// boost::lexical_cast<T>(value) — безопасное приведение между типами
// через текстовое представление.
//
// Преимущество: бросает boost::bad_lexical_cast при ошибке.
//
// ПРИМЕР С BOOST (требует установки):
//   #include <boost/lexical_cast.hpp>
//
//   try {
//       int n = boost::lexical_cast<int>("42");
//       double d = boost::lexical_cast<double>("3.14");
//       std::string s = boost::lexical_cast<std::string>(255);
//   } catch (const boost::bad_lexical_cast& e) {
//       std::cout << "Ошибка: " << e.what() << std::endl;
//   }
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 3: Boost.String Algorithms
// ─────────────────────────────────────────────────────────────────────────────
//
// #include <boost/algorithm/string.hpp>
//
// Основные функции:
//   boost::to_upper(str)           — перевести в верхний регистр (на месте)
//   boost::trim(str)               — удалить пробелы с обоих концов
//   boost::replace_all(str, f, t)  — заменить все вхождения
//   boost::split(vec, str, pred)   — разбить строку (аналог Python split())
//   boost::join(vec, sep)          — объединить (аналог Python join())
//   boost::starts_with(str, pref)  — начинается ли с префикса
//   boost::iequals(a, b)           — сравнение без учёта регистра
//
// ПРИМЕР С BOOST:
//   std::string s = "  Hello, World!  ";
//   boost::trim(s);                  // "Hello, World!"
//
//   std::vector<std::string> words;
//   boost::split(words, "a,b,c", boost::is_any_of(","));
//   // words = {"a", "b", "c"}
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 4: Boost.Filesystem → std::filesystem (C++17)
// ─────────────────────────────────────────────────────────────────────────────
//
// Boost.Filesystem — работа с файловой системой.
// В C++17 std::filesystem — это практически тот же API!
//
// Основные операции:
//   fs::path p("/home/user/file.txt")  — создать путь
//   p.filename()                        — "file.txt"
//   p.extension()                       — ".txt"
//   p.parent_path()                    — "/home/user"
//   p / "subdir" / "file"              — объединение путей (operator/)
//
//   fs::exists(p)                  — существует ли путь
//   fs::is_regular_file(p)         — это обычный файл?
//   fs::is_directory(p)            — это директория?
//   fs::file_size(p)               — размер файла в байтах
//   fs::create_directory(p)        — создать директорию
//   fs::create_directories(p)      — создать со всеми родительскими
//   fs::copy_file(from, to)        — скопировать файл
//   fs::remove(p)                  — удалить файл
//   fs::remove_all(p)              — удалить директорию рекурсивно
//   fs::rename(from, to)           — переименовать/переместить
//   fs::current_path()             — текущая директория
//
// Перебор директории:
//   for (const auto& entry : fs::directory_iterator(dir)) {
//       std::cout << entry.path().filename() << std::endl;
//   }
//   for (const auto& entry : fs::recursive_directory_iterator(dir)) {
//       std::cout << entry.path() << std::endl;
//   }
// ─────────────────────────────────────────────────────────────────────────────

// Демо-реализация boost::lexical_cast (без зависимостей):
template<typename Target, typename Source>
Target lexical_cast_demo(const Source& arg) {
    std::stringstream ss;
    ss << arg;
    Target result{};
    if (!(ss >> result)) {
        throw std::runtime_error("Ошибка преобразования типов");
    }
    return result;
}

// Демо-реализация boost::split (без зависимостей):
std::vector<std::string> split_demo(const std::string& str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        if (!token.empty()) {
            result.push_back(token);
        }
    }
    return result;
}

// Демо-реализация boost::trim (без зависимостей):
std::string trim_demo(const std::string& s) {
    auto start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

// Демо-реализация boost::to_upper (без зависимостей):
std::string to_upper_demo(std::string s) {
    for (char& c : s) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return s;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Урок 14: Boost — Введение" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "ВАЖНО: Этот урок содержит документацию и примеры кода Boost." << std::endl;
    std::cout << "Реальный код Boost требует установки библиотеки." << std::endl;
    std::cout << "Демонстрационный код использует стандартную библиотеку C++17." << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 1. Аналог boost::lexical_cast
    // =========================================================================
    std::cout << "--- 1. Аналог boost::lexical_cast ---" << std::endl;

    try {
        int n = lexical_cast_demo<int>(std::string("42"));
        double d = lexical_cast_demo<double>(std::string("3.14"));
        std::string s = lexical_cast_demo<std::string>(255);

        std::cout << "lexical_cast<int>(\"42\") = " << n << std::endl;
        std::cout << "lexical_cast<double>(\"3.14\") = " << d << std::endl;
        std::cout << "lexical_cast<string>(255) = \"" << s << "\"" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Ошибка преобразования:
    try {
        lexical_cast_demo<int>(std::string("abc"));
    } catch (const std::runtime_error& e) {
        std::cout << "Ожидаемая ошибка: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    // =========================================================================
    // 2. Аналог boost::split и boost::join
    // =========================================================================
    std::cout << "--- 2. Аналог boost::split ---" << std::endl;

    std::string csv = "яблоко,банан,вишня,персик";
    auto fruits = split_demo(csv, ',');

    std::cout << "Исходная строка: '" << csv << "'" << std::endl;
    std::cout << "После split(','), " << fruits.size() << " элементов:" << std::endl;
    for (const auto& f : fruits) {
        std::cout << "  - " << f << std::endl;
    }

    // Аналог boost::join:
    std::string joined;
    for (size_t i = 0; i < fruits.size(); ++i) {
        if (i > 0) joined += " | ";
        joined += fruits[i];
    }
    std::cout << "После join(' | '): " << joined << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 3. Аналог boost::trim и boost::to_upper
    // =========================================================================
    std::cout << "--- 3. Аналог boost::trim и boost::to_upper ---" << std::endl;

    std::string padded = "   Hello, Boost!   ";
    std::string trimmed = trim_demo(padded);
    std::string upper = to_upper_demo(trimmed);

    std::cout << "До trim:       '" << padded << "'" << std::endl;
    std::cout << "После trim:    '" << trimmed << "'" << std::endl;
    std::cout << "После to_upper: '" << upper << "'" << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 4. boost::optional → std::optional (C++17)
    // =========================================================================
    std::cout << "--- 4. boost::optional (std::optional в C++17) ---" << std::endl;

    auto safe_sqrt = [](double x) -> std::optional<double> {
        if (x < 0) return std::nullopt;
        return std::sqrt(x);
    };

    auto r1 = safe_sqrt(16.0);
    auto r2 = safe_sqrt(-4.0);

    std::cout << "safe_sqrt(16) = "
              << (r1.has_value() ? std::to_string(*r1) : "нет значения") << std::endl;
    std::cout << "safe_sqrt(-4) = "
              << (r2.has_value() ? std::to_string(*r2) : "нет значения") << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 5. boost::filesystem → std::filesystem (C++17)
    // =========================================================================
    std::cout << "--- 5. boost::filesystem (std::filesystem в C++17) ---" << std::endl;

    namespace fs = std::filesystem;

    fs::path current = fs::current_path();
    std::cout << "Текущая директория: " << current << std::endl;

    // Работа с путями:
    fs::path example_path = current / "lessons" / "lesson_01.cpp";
    std::cout << "Путь: " << example_path << std::endl;
    std::cout << "  filename():   " << example_path.filename() << std::endl;
    std::cout << "  stem():       " << example_path.stem() << std::endl;
    std::cout << "  extension():  " << example_path.extension() << std::endl;
    std::cout << "  parent_path(): " << example_path.parent_path().filename() << std::endl;

    // Подсчёт файлов:
    int file_count = 0;
    int dir_count = 0;
    try {
        for (const auto& entry : fs::directory_iterator(current)) {
            if (fs::is_regular_file(entry)) ++file_count;
            else if (fs::is_directory(entry)) ++dir_count;
        }
    } catch (const std::exception& e) {
        std::cout << "Ошибка обхода директории: " << e.what() << std::endl;
    }
    std::cout << "В текущей директории: " << file_count
              << " файлов, " << dir_count << " директорий" << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 6. Установка Boost
    // =========================================================================
    std::cout << "--- 6. Установка Boost ---" << std::endl;
    std::cout << "macOS:   brew install boost" << std::endl;
    std::cout << "Ubuntu:  sudo apt install libboost-all-dev" << std::endl;
    std::cout << "Windows: vcpkg install boost" << std::endl;
    std::cout << std::endl;
    std::cout << "Компиляция с Boost.Filesystem:" << std::endl;
    std::cout << "  g++     -std=c++17 file.cpp -lboost_filesystem -lboost_system" << std::endl;
    std::cout << "  clang++ -std=c++17 file.cpp -lboost_filesystem -lboost_system" << std::endl;
    std::cout << std::endl;
    std::cout << "С CMake (CMakeLists.txt):" << std::endl;
    std::cout << "  find_package(Boost REQUIRED COMPONENTS filesystem system)" << std::endl;
    std::cout << "  target_link_libraries(myapp Boost::filesystem Boost::system)" << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 14 завершён!" << std::endl;
    std::cout << "  Следующий урок: Boost.Asio — асинхронный ввод-вывод" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "ДОМАШНЕЕ ЗАДАНИЕ:" << std::endl;
    std::cout << "1. Установите Boost и скомпилируйте пример с Boost.Filesystem" << std::endl;
    std::cout << "2. Напишите программу обхода директории рекурсивно" << std::endl;
    std::cout << "3. Используйте boost::split для разбора CSV-строки" << std::endl;
    std::cout << "4. Реализуйте конвертер типов через boost::lexical_cast" << std::endl;
    std::cout << "5. Изучите std::filesystem (C++17) — сравните с Boost.Filesystem" << std::endl;

    return 0;
}
