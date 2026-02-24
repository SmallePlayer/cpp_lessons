// =============================================================================
//  2: Переменные, типы данных и операторы
// =============================================================================
// Темы:
//   - Объявление и инициализация переменных
//   - Целочисленные типы (int, short, long, long long)
//   - Типы с плавающей точкой (float, double)
//   - Размеры типов и sizeof
//   - Арифметические операторы (+, -, *, /, %)
//   - Целочисленное деление и остаток
//   - Приведение типов (static_cast)
//   - Константы (const, constexpr)
//   - Литералы и суффиксы
//
// Аналогия с Python:
//   Python: x = 10 (тип определяется автоматически)
//   C++:    int x = 10; (тип указывается явно!)
//   Python: type(x) → <class 'int'>
//   C++:    sizeof(x) → 4 (размер в байтах)
// =============================================================================

#include <iostream>
#include <climits>    // INT_MAX, INT_MIN и т.д.
#include <cfloat>     // FLT_MAX, DBL_MAX
#include <cstdint>    // int8_t, int16_t, int32_t, int64_t (фиксированные размеры)

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   2: Переменные и типы данных" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =====================================================================
    // 1. СЫ ТЫ
    // =====================================================================
    //  В Python есть только int (неограниченной длины).
    //  В C++ есть СЬ целочисленных типов разного размера:
    //
    //  Тип          | Размер (обычно) | Диапазон
    //  -------------|-----------------|----------------------------------
    //  short        | 2 байта         | -32768 до 32767
    //  int          | 4 байта         | -2,147,483,648 до 2,147,483,647
    //  long         | 4 или 8 байт    | зависит от платформы
    //  long long    | 8 байт          | ±9.2 × 10^18
    //
    //  unsigned — беззнаковые версии (только положительные):
    //  unsigned int | 4 байта         | 0 до 4,294,967,295
    //
    // : unsigned типы СЫ! При вычитании могут "перетечь":
    //   unsigned int x = 0; x = x - 1; // → 4294967295 ( -1!)
    //   Рекомендация: не используйте unsigned, кроме битовых операций.

    std::cout << "--- 1. Целочисленные типы ---" << std::endl;

    short    s{100};
    int      i{200000};
    long     l{3000000L};
    long long ll{9000000000LL};

    std::cout << "short:     " << s  << " (размер: " << sizeof(short) << " байт)" << std::endl;
    std::cout << "int:       " << i  << " (размер: " << sizeof(int) << " байт)" << std::endl;
    std::cout << "long:      " << l  << " (размер: " << sizeof(long) << " байт)" << std::endl;
    std::cout << "long long: " << ll << " (размер: " << sizeof(long long) << " байт)" << std::endl;
    std::cout << std::endl;

    // Диапазоны:
    std::cout << "Диапазон int: " << INT_MIN << " до " << INT_MAX << std::endl;
    std::cout << "Диапазон long long: " << LLONG_MIN << " до " << LLONG_MAX << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 2. ТЫ С СЫ  (C++11)
    // =====================================================================
    // азмеры short, int, long СЯТ от платформы!
    // ля гарантированного размера используйте типы из <cstdint>:
    //   int8_t, int16_t, int32_t, int64_t    — знаковые
    //   uint8_t, uint16_t, uint32_t, uint64_t — беззнаковые
    //
    // Самые часто используемые:
    //   std::int32_t  — гарантированно 32 бита
    //   std::int64_t  — гарантированно 64 бита

    std::cout << "--- 2. Фиксированные типы ---" << std::endl;
    std::int32_t fixed32{42};
    std::int64_t fixed64{123456789012345LL};
    std::cout << "int32_t: " << fixed32 << " (размер: " << sizeof(fixed32) << ")" << std::endl;
    std::cout << "int64_t: " << fixed64 << " (размер: " << sizeof(fixed64) << ")" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 3. С С Щ Т
    // =====================================================================
    //  В Python есть только float (это double в C++).
    //
    //  Тип         | Размер  | Точность           | Суффикс
    //  ------------|---------|--------------------|---------
    //  float       | 4 байта | ~7 значащих цифр   | f или F
    //  double      | 8 байт  | ~15 значащих цифр  | (по умолчанию)
    //  long double | 8-16    | ≥15 цифр           | l или L
    //
    // : Числа с плавающей точкой не ТЫ!
    //   0.1 + 0.2 ≠ 0.3 (как и в Python!)
    //   Это особенность IEEE 754, а не бага языка.

    std::cout << "--- 3. Числа с плавающей точкой ---" << std::endl;

    float  f_val{3.14f};         // ЯТЬ суффикс f!
    double d_val{3.14159265358979};
    long double ld_val{3.14159265358979323846L};

    std::cout << "float:       " << f_val  << " (размер: " << sizeof(float) << ")" << std::endl;
    std::cout << "double:      " << d_val  << " (размер: " << sizeof(double) << ")" << std::endl;
    std::cout << "long double: " << ld_val << " (размер: " << sizeof(long double) << ")" << std::endl;

    // Проблема точности:
    std::cout << "0.1 + 0.2 = " << (0.1 + 0.2) << std::endl;
    std::cout << "0.1 + 0.2 == 0.3? " << std::boolalpha << (0.1 + 0.2 == 0.3) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 4. char  bool
    // =====================================================================
    // char — хранит  символ (или число от -128 до 127).
    //   Символ заключается в Ы кавычки: 'A'
    //   Строка — в Ы: "Hello"
    //
    // bool — true (1) или false (0).
    //    Python: True/False (с большой буквы)
    //    C++:    true/false (с маленькой буквы)

    std::cout << "--- 4. char и bool ---" << std::endl;

    char letter{'A'};
    char digit{'5'};
    char newline{'\n'};
    bool is_ready{true};
    bool is_done{false};

    std::cout << "char letter: " << letter << " (ASCII код: " << static_cast<int>(letter) << ")" << std::endl;
    std::cout << "char digit:  " << digit << " (ASCII код: " << static_cast<int>(digit) << ")" << std::endl;
    std::cout << "bool is_ready: " << std::boolalpha << is_ready << std::endl;
    std::cout << "bool is_done:  " << std::boolalpha << is_done << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 5. sizeof —  Т  ТХ
    // =====================================================================
    // sizeof(тип) или sizeof переменная — возвращает размер в байтах
    // Аналог в Python: sys.getsizeof(x) (но показывает полный объём объекта)

    std::cout << "--- 5. sizeof ---" << std::endl;
    std::cout << "sizeof(bool):      " << sizeof(bool) << " байт" << std::endl;
    std::cout << "sizeof(char):      " << sizeof(char) << " байт" << std::endl;
    std::cout << "sizeof(short):     " << sizeof(short) << " байт" << std::endl;
    std::cout << "sizeof(int):       " << sizeof(int) << " байт" << std::endl;
    std::cout << "sizeof(long):      " << sizeof(long) << " байт" << std::endl;
    std::cout << "sizeof(long long): " << sizeof(long long) << " байт" << std::endl;
    std::cout << "sizeof(float):     " << sizeof(float) << " байт" << std::endl;
    std::cout << "sizeof(double):    " << sizeof(double) << " байт" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 6. ТС ТЫ
    // =====================================================================
    // Всё как в Python, но:
    //   Деление целых чисел: 7 / 2 = 3 ( 3.5!)
    //    В Python 3: 7 / 2 = 3.5, 7 // 2 = 3
    //    C++: 7 / 2 = 3 (целочисленное деление!)
    //   Для дробного результата: 7.0 / 2 = 3.5
    //
    //   Оператор % (остаток): 7 % 2 = 1
    //   ТТ ТЬ С Ы С (в C++)!
    //    Python % работает и с float.

    std::cout << "--- 6. Арифметические операторы ---" << std::endl;

    int a_op{10}, b_op{3};
    std::cout << "a = " << a_op << ", b = " << b_op << std::endl;
    std::cout << "a + b = " << (a_op + b_op) << std::endl;
    std::cout << "a - b = " << (a_op - b_op) << std::endl;
    std::cout << "a * b = " << (a_op * b_op) << std::endl;
    std::cout << "a / b = " << (a_op / b_op) << " (С деление!)" << std::endl;
    std::cout << "a % b = " << (a_op % b_op) << " (остаток от деления)" << std::endl;
    std::cout << std::endl;

    // Деление с плавающей точкой:
    double da{10.0}, db{3.0};
    std::cout << "10.0 / 3.0 = " << (da / db) << " (дробный результат)" << std::endl;
    std::cout << "static_cast<double>(10) / 3 = " << (static_cast<double>(10) / 3) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 7. ССТЫ ТЫ СЯ
    // =====================================================================
    // Как в Python: +=, -=, *=, /=, %=
    //  В C++ дополнительно есть: ++, -- (инкремент и декремент)
    //   ++x  — увеличить x на 1 до использованием (prefix)
    //   x++  — увеличить x на 1 после использования (postfix)
    //
    // Python: x += 1 (нет ++ в Python!)
    // C++:    x++; или ++x;

    std::cout << "--- 7. Составные операторы ---" << std::endl;

    int val{10};
    std::cout << "val = " << val << std::endl;

    val += 5;  std::cout << "val += 5 → " << val << std::endl;
    val -= 3;  std::cout << "val -= 3 → " << val << std::endl;
    val *= 2;  std::cout << "val *= 2 → " << val << std::endl;
    val /= 4;  std::cout << "val /= 4 → " << val << std::endl;
    val %= 3;  std::cout << "val %= 3 → " << val << std::endl;
    std::cout << std::endl;

    // Инкремент и декремент:
    int counter{5};
    std::cout << "counter = " << counter << std::endl;
    std::cout << "++counter = " << (++counter) << " (сначала +1, потом использовать)" << std::endl;
    std::cout << "counter++ = " << (counter++) << " (сначала использовать, потом +1)" << std::endl;
    std::cout << "counter теперь = " << counter << std::endl;
    std::cout << "--counter = " << (--counter) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 8.  Т (TYPE CASTING)
    // =====================================================================
    //  В Python: int(3.14) → 3, float(5) → 5.0, str(42) → "42"
    //
    //  В C++ есть несколько видов приведения:
    //
    // 1. Неявное (implicit) — компилятор делает сам:
    //    int x = 3; double d = x;  // int → double (безопасно)
    //
    // 2. Явное (explicit) через static_cast<тип>(значение):
    //    double d = 3.14;
    //    int x = static_cast<int>(d);  // 3 (отбрасывает дробную часть)
    //
    // 3. C-style cast (не рекомендуется!):
    //    int x = (int)3.14;  // Работает, но опасно
    //
    // Всегда используйте static_cast — он безопаснее и виднее в коде!

    std::cout << "--- 8. Приведение типов ---" << std::endl;

    double pi{3.14159};
    int pi_int = static_cast<int>(pi);  // 3 (дробная часть отброшена)
    std::cout << "double pi = " << pi << std::endl;
    std::cout << "static_cast<int>(pi) = " << pi_int << std::endl;

    char ch{'A'};
    int ascii_code = static_cast<int>(ch);  // 65
    std::cout << "char 'A' как int = " << ascii_code << std::endl;

    // Неявное преобразование:
    int small{42};
    double big = small;  // int → double (безопасно, без потери данных)
    std::cout << "int 42 → double: " << big << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 9. СТТЫ: const  constexpr
    // =====================================================================
    // const — значение нельзя изменить после инициализации
    //   Как final в Java или UPPER_CASE в Python (по соглашению)
    //
    // constexpr (C++11) — значение известно на этапе компиляции
    //   Компилятор вычисляет значение заранее, до запуска программы
    //   Это быстрее, чем const!
    //
    // Python: MAX_SIZE = 100  (по соглашению, но можно изменить!)
    // C++:    const int MAX_SIZE = 100;  (ЬЯ изменить — ошибка компиляции!)

    std::cout << "--- 9. Константы ---" << std::endl;

    const double GRAVITY{9.81};
    constexpr int MAX_STUDENTS{30};
    constexpr double TAX_RATE{0.13};

    std::cout << "const GRAVITY = " << GRAVITY << std::endl;
    std::cout << "constexpr MAX_STUDENTS = " << MAX_STUDENTS << std::endl;
    std::cout << "constexpr TAX_RATE = " << TAX_RATE << std::endl;

    // GRAVITY = 10.0;  // Ш: assignment of read-only variable!
    // MAX_STUDENTS = 50;  // Ш: нельзя изменить constexpr!
    std::cout << std::endl;

    // =====================================================================
    // 10. auto — ТТС  Т (C++11)
    // =====================================================================
    // auto позволяет компилятору самому определить тип переменной
    // по значению, которым она инициализируется.
    //
    // auto x = 42;       // int
    // auto y = 3.14;     // double
    // auto s = "hello";  // const char* ( std::string!)
    //
    // Python: x = 42 (тип всегда определяется автоматически)
    // C++:    auto x = 42; (тип определяется компилятором)
    //
    // : auto ТТ инициализации!
    //   auto x;  // Ш — компилятор не знает тип!

    std::cout << "--- 10. auto ---" << std::endl;

    auto auto_int = 42;
    auto auto_double = 3.14;
    auto auto_bool = true;
    auto auto_char = 'X';

    std::cout << "auto 42 → int:    " << auto_int << std::endl;
    std::cout << "auto 3.14 → double: " << auto_double << std::endl;
    std::cout << "auto true → bool:  " << std::boolalpha << auto_bool << std::endl;
    std::cout << "auto 'X' → char:   " << auto_char << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 11.  (OVERFLOW)
    // =====================================================================
    //  В Python целые числа не переполняются — они растут бесконечно.
    //  В C++ — переполняются! Это Undefined Behavior для signed типов!
    //
    // int max = INT_MAX;     // 2147483647
    // max = max + 1;         // UB! (обычно станет -2147483648)
    //
    // Для unsigned: «оборачивается» (wrap around)
    //   unsigned int x = 0;
    //   x = x - 1;  // → 4294967295 (UINT_MAX)

    std::cout << "--- 11. Переполнение ---" << std::endl;
    std::cout << "INT_MAX = " << INT_MAX << std::endl;
    std::cout << "INT_MIN = " << INT_MIN << std::endl;
    // Демонстрация unsigned overflow (defined behavior):
    unsigned int u_max = UINT_MAX;
    std::cout << "UINT_MAX = " << u_max << std::endl;
    std::cout << "UINT_MAX + 1 = " << (u_max + 1) << " (wrap around!)" << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 2 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. Напишите программу-калькулятор для двух чисел" << std::endl;
    std::cout << "2. Вычислите площадь круга (pi * r * r)" << std::endl;
    std::cout << "3. Конвертируйте температуру: Цельсий → Фаренгейт" << std::endl;
    std::cout << "4. Поэкспериментируйте с sizeof для всех типов" << std::endl;
    std::cout << "5. Попробуйте присвоить новое значение const переменной" << std::endl;

    return 0;
}