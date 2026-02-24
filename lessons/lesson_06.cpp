// =============================================================================
//  6: Функции
// =============================================================================
// Темы:
//   - Объявление и определение функций
//   - Параметры и аргументы
//   - Возвращаемое значение (return)
//   - Передача по значению, по ссылке, по константной ссылке
//   - Значения по умолчанию
//   - Перегрузка функций (overloading)
//   - Прототипы (forward declaration)
//   - inline функции
//   - Рекурсия
//
// Аналогия с Python:
//   Python: def add(a, b):          →  C++: int add(int a, int b) {
//               return a + b                    return a + b;
//                                           }
//   Python: def greet(name="Мир"):  →  C++: void greet(std::string name = "Мир")
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// ─────────────────────────────────────────────────────────────────────────────
// ТЯ: Прототипы функций (Forward Declarations)
// ─────────────────────────────────────────────────────────────────────────────
//  В C++ функция должна быть объявлена до использования.
// Прототип (объявление) — говорит компилятору: «такая функция существует».
// Определение (с телом) — описывает, что делает функция.
//
// Прототип: тип_возврата имя(типы параметров);
// Определение: тип_возврата имя(параметры) { тело }
//
//  В Python: порядок определения не важен (интерпретатор сначала
// читает весь файл).  В C++: нужно объявить до использования!
// ─────────────────────────────────────────────────────────────────────────────

// Прототипы функций (объявления):
int add(int a, int b);
double average(double a, double b);
void print_separator(char symbol = '-', int width = 40);
void greet(const std::string& name = "Мир");
void swap_values(int& a, int& b);
int factorial(int n);
double power(double base, int exponent);
std::string repeat_string(const std::string& str, int times);

// Перегрузка:
int multiply(int a, int b);
double multiply(double a, double b);
int multiply(int a, int b, int c);

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   6: Функции" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =====================================================================
    // 1. СТЫ  С Т Я
    // =====================================================================
    // int add(int a, int b) { return a + b; }
    //
    // int — тип возвращаемого значения
    // add — имя функции
    // int a, int b — параметры (с типами!)
    // return a + b — возвращаемое значение
    //
    //  В Python тип возврата не указывается (можно вернуть что угодно)
    //  В C++ тип возврата обязателен и фиксирован

    std::cout << "--- 1. Простые функции ---" << std::endl;

    int sum = add(10, 20);
    std::cout << "add(10, 20) = " << sum << std::endl;

    double avg = average(4.5, 5.5);
    std::cout << "average(4.5, 5.5) = " << avg << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 2. void  ( Т)
    // =====================================================================
    // void — означает «функция ничего не возвращает»
    //
    // Python: def print_hello():     (может не иметь return)
    // C++:    void print_hello() { }  (явно пишем void)

    std::cout << "--- 2. void функции ---" << std::endl;

    print_separator();              // Используем значения по умолчанию
    greet();                        // "Привет, Мир!"
    greet("Алексей");               // "Привет, Алексей!"
    print_separator('=', 30);       // ==============================
    std::cout << std::endl;

    // =====================================================================
    // 3.    vs  ССЫ
    // =====================================================================
    // ередача по значению (by value):
    //   void func(int x) — создаёт копию. Изменения внутри не влияют на оригинал.
    //
    // ередача по ссылке (by reference):
    //   void func(int& x) — работает с оригиналом. Изменения видны снаружи!
    //
    // ередача по константной ссылке (by const reference):
    //   void func(const int& x) — не копирует, но не позволяет изменять.
    //   Рекомендуется для больших объектов (строки, вектора и т.д.)
    //
    // Python: всё передаётся "по ссылке на объект"
    //   Мутабельные (list, dict) — можно изменить внутри функции
    //   Иммутабельные (int, str) — нельзя изменить
    //
    // C++: всегда явно указывайте способ передачи!
    //
    //  (learncpp.com):
    //   - Простые типы (int, double, char, bool) → по значению
    //   - Строки, вектора, объекты → по const ссылке (const std::string&)
    //   - Если нужно изменить → по ссылке (int& x)

    std::cout << "--- 3. Передача по значению vs по ссылке ---" << std::endl;

    int x{10}, y{20};
    std::cout << "До swap: x = " << x << ", y = " << y << std::endl;
    swap_values(x, y);  // ередача по ссылке — изменяет оригинал!
    std::cout << "После swap: x = " << x << ", y = " << y << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 4. Я  
    // =====================================================================
    // Как и в Python, параметры могут иметь значения по умолчанию.
    // : Параметры со значениями по умолчанию должны идти последними!
    //
    // Python: def greet(name="ир"):
    // C++:    void greet(const std::string& name = "ир")
    //
    // : значения по умолчанию указываются в объявлении (прототипе),
    //          а  в определении (если они разделены).

    std::cout << "--- 4. Значения по умолчанию ---" << std::endl;

    print_separator();            // '-' и 40
    print_separator('*');         // '*' и 40
    print_separator('=', 20);    // '=' и 20
    std::cout << std::endl;

    // =====================================================================
    // 5.   (OVERLOADING)
    // =====================================================================
    //  В C++ можно создать несколько функций с одинаковым именем,
    // но разными параметрами! Компилятор выберет нужную по аргументам.
    //
    // Python: Нет перегрузки! Можно использовать *args, **kwargs.
    // C++:    int multiply(int, int)
    //         double multiply(double, double)
    //         int multiply(int, int, int)

    std::cout << "--- 5. Перегрузка функций ---" << std::endl;

    std::cout << "multiply(3, 4) = " << multiply(3, 4) << std::endl;
    std::cout << "multiply(2.5, 3.0) = " << multiply(2.5, 3.0) << std::endl;
    std::cout << "multiply(2, 3, 4) = " << multiply(2, 3, 4) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 6. СЯ
    // =====================================================================
    // Функция вызывает саму себя. Нужен BASE CASE (условие выхода)!
    //
    // : в C++ нет ограничения глубины рекурсии (как в Python,
    // где по умолчанию ~1000). Но стек памяти ограничен → Stack Overflow!
    //
    // Python: sys.setrecursionlimit(10000)
    // C++:    ограничен размером стека (обычно 1-8 МБ)

    std::cout << "--- 6. Рекурсия ---" << std::endl;

    std::cout << "5! = " << factorial(5) << std::endl;
    std::cout << "10! = " << factorial(10) << std::endl;
    std::cout << "2^10 = " << power(2.0, 10) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 7.  С СТ  Т
    // =====================================================================
    std::cout << "--- 7. Функции со строками ---" << std::endl;

    std::string repeated = repeat_string("Ha", 3);
    std::cout << "repeat_string(\"Ha\", 3) = '" << repeated << "'" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 8. Я-ЫЯ (C++11)
    // =====================================================================
    // Лямбда — анонимная функция, определённая прямо в коде.
    //
    // Синтаксис: [захват](параметры) -> тип_возврата { тело }
    //
    // [захват] — какие переменные из окружения доступны:
    //   []    — ничего не захватывать
    //   [=]   — всё по значению (копия)
    //   [&]   — всё по ссылке
    //   [x]   — переменную x по значению
    //   [&x]  — переменную x по ссылке
    //   [=, &x] — всё по значению, кроме x по ссылке
    //
    // Python: lambda x, y: x + y
    // C++:    [](int x, int y) { return x + y; }
    //
    // Python лямбды — только одно выражение!
    // C++ лямбды — могут содержать любой код!

    std::cout << "--- 8. Лямбда-выражения ---" << std::endl;

    // Простая лямбда:
    auto add_lambda = [](int a, int b) { return a + b; };
    std::cout << "add_lambda(3, 7) = " << add_lambda(3, 7) << std::endl;

    // Лямбда с захватом:
    int multiplier{3};
    auto times_n = [multiplier](int x) { return x * multiplier; };
    std::cout << "times_3(5) = " << times_n(5) << std::endl;

    // Лямбда с захватом по ссылке:
    int total{0};
    auto accumulate = [&total](int x) { total += x; };
    accumulate(10);
    accumulate(20);
    accumulate(30);
    std::cout << "total после accumulate(10,20,30) = " << total << std::endl;

    // Лямбда с вектором:
    std::vector<int> nums{5, 2, 8, 1, 9, 3};
    std::cout << "Чётные числа: ";
    for (const auto& n : nums) {
        auto is_even = [](int x) { return x % 2 == 0; };
        if (is_even(n)) {
            std::cout << n << " ";
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 6 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. Напишите функцию is_prime(int n) → bool" << std::endl;
    std::cout << "2. Напишите функцию fibonacci(int n) → вектор чисел" << std::endl;
    std::cout << "3. Напишите перегруженную функцию max для int, double, string" << std::endl;
    std::cout << "4. Реализуйте бинарный поиск рекурсивно" << std::endl;
    std::cout << "5. Используйте лямбду для сортировки вектора строк по длине" << std::endl;

    return 0;
}

// ═══════════════════════════════════════════════════════════════════════════════
// Определения функций (после main)
// ═══════════════════════════════════════════════════════════════════════════════

int add(int a, int b) {
    return a + b;
}

double average(double a, double b) {
    return (a + b) / 2.0;
}

// Значения по умолчанию — только в прототипе!
void print_separator(char symbol, int width) {
    for (int i{0}; i < width; ++i) {
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void greet(const std::string& name) {
    std::cout << "Привет, " << name << "!" << std::endl;
}

void swap_values(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int factorial(int n) {
    if (n <= 1) return 1;       // Base case
    return n * factorial(n - 1); // Рекурсивный вызов
}

double power(double base, int exponent) {
    if (exponent == 0) return 1.0;
    if (exponent < 0) return 1.0 / power(base, -exponent);
    return base * power(base, exponent - 1);
}

std::string repeat_string(const std::string& str, int times) {
    std::string result;
    for (int i{0}; i < times; ++i) {
        result += str;
    }
    return result;
}

// Перегруженные функции:
int multiply(int a, int b) {
    return a * b;
}

double multiply(double a, double b) {
    return a * b;
}

int multiply(int a, int b, int c) {
    return a * b * c;
}