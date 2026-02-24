// =============================================================================
//  3: Строки в C++ (std::string и std::string_view)
// =============================================================================
// Темы:
//   - C-строки (const char*) vs std::string
//   - Создание и инициализация строк
//   - Операции со строками: конкатенация, сравнение, поиск
//   - Методы std::string (length, substr, find, replace, etc.)
//   - std::string_view (C++17) — лёгкий «взгляд» на строку
//   - std::getline для ввода строк с пробелами
//   - Конвертация строк ↔ числа
//
// Аналогия с Python:
//   Python: name = "Hello"         →  C++: std::string name = "Hello";
//   Python: len(name)              →  C++: name.length()  или  name.size()
//   Python: name + " World"        →  C++: name + " World"
//   Python: name[0]                →  C++: name[0]  или  name.at(0)
//   Python: "lo" in name           →  C++: name.find("lo") != std::string::npos
// =============================================================================

#include <iostream>
#include <string>        // std::string
#include <string_view>   // std::string_view (C++17)
#include <cctype>        // toupper, tolower, isdigit и т.д.

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   3: Строки в C++" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =====================================================================
    // 1. C-СТ vs std::string
    // =====================================================================
    //  C строки — это массивы символов, заканчивающиеся нулевым символом '\0':
    //   const char* greeting = "Hello";  // → ['H','e','l','l','o','\0']
    //
    // Проблемы C-строк:
    //   - Нет автоматического управления памятью
    //   - Легко выйти за границы массива
    //   - Нельзя легко конкатенировать, сравнивать и т.д.
    //
    // std::string (C++) — это СС, который:
    //   - Автоматически управляет памятью
    //   - Может расти и уменьшаться
    //   - Имеет удобные методы
    //   - Безопасен
    //
    // : С используйте std::string, а не C-строки!

    std::cout << "--- 1. C-строки vs std::string ---" << std::endl;

    // C-строка (не рекомендуется):
    const char* c_str = "Привет из C";  // казатель на массив символов
    std::cout << "C-строка: " << c_str << std::endl;

    // std::string (ТСЯ):
    std::string cpp_str = "Привет из C++";
    std::cout << "std::string: " << cpp_str << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 2. С СТ
    // =====================================================================
    std::cout << "--- 2. Создание строк ---" << std::endl;

    std::string s1;                        // устая строка ""
    std::string s2{"Hello"};               // Списковая инициализация
    std::string s3 = "World";              // Копирующая инициализация
    std::string s4(5, '*');                 // "*****" (5 звёздочек)
    std::string s5{s2};                    // Копия s2
    std::string s6{s2, 1, 3};             // "ell" (от позиции 1, длина 3)

    std::cout << "s1 (пустая):    '" << s1 << "'" << std::endl;
    std::cout << "s2 {\"Hello\"}:   '" << s2 << "'" << std::endl;
    std::cout << "s3 = \"World\":   '" << s3 << "'" << std::endl;
    std::cout << "s4 (5, '*'):    '" << s4 << "'" << std::endl;
    std::cout << "s5 (копия s2):  '" << s5 << "'" << std::endl;
    std::cout << "s6 (s2,1,3):    '" << s6 << "'" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 3.  СТ  СТ  С
    // =====================================================================
    // length() и size() — одно и то же, возвращают длину строки
    // empty() — проверяет, пуста ли строка
    //
    // оступ к символам:
    //   str[i]    — без проверки границ (быстро, но опасно!)
    //   str.at(i) — с проверкой границ (бросает исключение при выходе)
    //   str.front() — первый символ
    //   str.back()  — последний символ
    //
    // Python: name[0], name[-1], len(name)
    // C++:    name[0], name.back(), name.length()
    // : в C++ нет отрицательных индексов! name[-1] — это UB!

    std::cout << "--- 3. Длина и доступ ---" << std::endl;

    std::string word{"Programming"};
    std::cout << "Строка: '" << word << "'" << std::endl;
    std::cout << "length(): " << word.length() << std::endl;
    std::cout << "size():   " << word.size() << std::endl;
    std::cout << "empty():  " << std::boolalpha << word.empty() << std::endl;
    std::cout << "word[0]:  " << word[0] << std::endl;
    std::cout << "word.at(3): " << word.at(3) << std::endl;
    std::cout << "front():  " << word.front() << std::endl;
    std::cout << "back():   " << word.back() << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 4. ТЯ СТ
    // =====================================================================
    // Оператор + соединяет строки (как в Python)
    // Оператор += добавляет к строке
    // append() — метод для добавления
    //
    // : Нельзя конкатенировать два литерала!
    //   "Hello" + " World"  — Ш! (это C-строки, а не std::string)
    //   std::string("Hello") + " World"  — !
    //   "Hello"s + " World"  — ! (с литералом s, C++14)

    std::cout << "--- 4. Конкатенация ---" << std::endl;

    std::string first{"Hello"};
    std::string second{" World"};
    std::string result = first + second;       // "Hello World"
    std::cout << "first + second = '" << result << "'" << std::endl;

    result += "!!!";                            // Добавляем к результату
    std::cout << "result += \"!!!\" → '" << result << "'" << std::endl;

    result.append(" C++");                      // Метод append
    std::cout << "result.append(\" C++\") → '" << result << "'" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 5. С СТ
    // =====================================================================
    // Операторы ==, !=, <, >, <=, >= — лексикографическое сравнение
    //  В Python: == сравнивает содержимое (так же!)
    //  В C++: == для std::string тоже сравнивает содержимое
    //
    // compare() — возвращает 0 если равны, <0 или >0 если нет

    std::cout << "--- 5. Сравнение строк ---" << std::endl;

    std::string sa{"apple"};
    std::string sb{"banana"};
    std::string sc{"apple"};

    std::cout << "\"apple\" == \"apple\":  " << std::boolalpha << (sa == sc) << std::endl;
    std::cout << "\"apple\" == \"banana\": " << std::boolalpha << (sa == sb) << std::endl;
    std::cout << "\"apple\" < \"banana\":  " << std::boolalpha << (sa < sb) << std::endl;
    std::cout << "\"apple\" > \"banana\":  " << std::boolalpha << (sa > sb) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 6. С  СТХ
    // =====================================================================
    // find(что)       — находит первое вхождение, возвращает позицию
    // rfind(что)      — находит последнее вхождение
    // find_first_of() — находит первый из указанных символов
    //
    // Если не найдено — возвращает std::string::npos
    //
    // Python: str.find("lo") → 3 (или -1 если нет)
    // C++:    str.find("lo") → 3 (или std::string::npos если нет)

    std::cout << "--- 6. Поиск в строках ---" << std::endl;

    std::string text{"Hello, World! Hello, C++!"};
    std::cout << "Текст: '" << text << "'" << std::endl;

    std::size_t pos = text.find("Hello");
    std::cout << "find(\"Hello\"):  позиция " << pos << std::endl;

    pos = text.find("Hello", 1);  // Поиск с позиции 1
    std::cout << "find(\"Hello\", 1): позиция " << pos << std::endl;

    pos = text.rfind("Hello");    // Последнее вхождение
    std::cout << "rfind(\"Hello\"): позиция " << pos << std::endl;

    pos = text.find("Python");
    if (pos == std::string::npos) {
        std::cout << "\"Python\" не найден (npos)" << std::endl;
    }
    std::cout << std::endl;

    // =====================================================================
    // 7. СТ  Я
    // =====================================================================
    // substr(pos, len) — извлекает подстроку
    // replace(pos, len, str) — заменяет часть строки
    // erase(pos, len) — удаляет часть строки
    // insert(pos, str) — вставляет подстроку
    // clear() — очищает строку
    //
    // Python: text[2:5], text.replace("old", "new")
    // C++:    text.substr(2, 3), text.replace(pos, len, "new")
    // :  Python replace заменяет все вхождения!
    //            C++ replace работает по позиции!

    std::cout << "--- 7. Подстроки и модификация ---" << std::endl;

    std::string original{"Hello, World!"};
    std::cout << "Оригинал: '" << original << "'" << std::endl;

    std::string sub = original.substr(7, 5);  // "World"
    std::cout << "substr(7, 5): '" << sub << "'" << std::endl;

    std::string modified = original;
    modified.replace(7, 5, "C++");            // "Hello, C++!"
    std::cout << "replace(7,5,\"C++\"): '" << modified << "'" << std::endl;

    modified.insert(0, ">>> ");               // ">>> Hello, C++!"
    std::cout << "insert(0, \">>> \"): '" << modified << "'" << std::endl;

    modified.erase(0, 4);                     // "Hello, C++!"
    std::cout << "erase(0, 4): '" << modified << "'" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 8.  С СТ
    // =====================================================================
    // 1. о индексу: for (std::size_t i = 0; i < str.size(); ++i)
    // 2. Range-based for: for (char c : str)  — Ы СС
    // 3. Range-based по ссылке: for (char& c : str) — можно изменять!
    //
    // Python: for c in text:
    // C++:    for (char c : text) { ... }

    std::cout << "--- 8. Перебор символов ---" << std::endl;

    std::string demo{"C++17"};

    std::cout << "По индексу:     ";
    for (std::size_t j = 0; j < demo.size(); ++j) {
        std::cout << demo[j] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Range-based for: ";
    for (char c : demo) {
        std::cout << c << ' ';
    }
    std::cout << std::endl;

    // Изменение через ссылку:
    std::string lower_str{"hello"};
    for (char& c : lower_str) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    std::cout << "toupper(\"hello\"): '" << lower_str << "'" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 9. ТЯ СТ ↔ С
    // =====================================================================
    // Строка → число:
    //   std::stoi(str)   → int
    //   std::stol(str)   → long
    //   std::stoll(str)  → long long
    //   std::stof(str)   → float
    //   std::stod(str)   → double
    //
    // Число → строка:
    //   std::to_string(число)
    //
    // Python: int("42"), str(42), float("3.14")
    // C++:    std::stoi("42"), std::to_string(42), std::stod("3.14")

    std::cout << "--- 9. Конвертация строк и чисел ---" << std::endl;

    // Строка → число:
    std::string num_str{"42"};
    int num = std::stoi(num_str);
    std::cout << "stoi(\"42\") = " << num << std::endl;

    std::string pi_str{"3.14159"};
    double pi_val = std::stod(pi_str);
    std::cout << "stod(\"3.14159\") = " << pi_val << std::endl;

    // Число → строка:
    int value{255};
    std::string value_str = std::to_string(value);
    std::cout << "to_string(255) = \"" << value_str << "\"" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 10. std::string_view (C++17) —  «Я»
    // =====================================================================
    // std::string_view — это  копия строки, а только «взгляд» на неё.
    // е выделяет память, не копирует данные.
    // деально для функций, которым нужно только прочитать строку.
    //
    // : string_view не владеет данными! Если оригинальная
    // строка будет удалена, string_view станет «висячей» ссылкой!
    //
    // Python аналогия: memoryview для bytes (похожая идея)

    std::cout << "--- 10. std::string_view (C++17) ---" << std::endl;

    std::string source{"Hello, wonderful World!"};
    std::string_view view{source};             // Не копирует!

    std::cout << "source: '" << source << "'" << std::endl;
    std::cout << "view:   '" << view << "'" << std::endl;
    std::cout << "view.length(): " << view.length() << std::endl;
    std::cout << "view.substr(7, 9): '" << view.substr(7, 9) << "'" << std::endl;

    // string_view тоже можно перебирать:
    std::cout << "Первые 5 символов: ";
    for (std::size_t k = 0; k < 5; ++k) {
        std::cout << view[k];
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 3 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. Напишите программу, которая переворачивает строку" << std::endl;
    std::cout << "2. Подсчитайте количество гласных в строке" << std::endl;
    std::cout << "3. Замените все пробелы на подчёркивания" << std::endl;
    std::cout << "4. Реализуйте проверку палиндрома" << std::endl;
    std::cout << "5. Разделите строку по запятым (аналог split)" << std::endl;

    return 0;
}