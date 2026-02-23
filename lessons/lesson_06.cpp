// =============================================================================
//  6: ункции
// =============================================================================
// Темы:
//   - бъявление и определение функций
//   - араметры и аргументы
//   - озвращаемое значение (return)
//   - ередача по значению, по ссылке, по константной ссылке
//   - начения по умолчанию
//   - ерегрузка функций (overloading)
//   - рототипы (forward declaration)
//   - inline функции
//   - екурсия
//
// налогия с Python:
//   Python: def add(a, b):          →  C++: int add(int a, int b) {
//               return a + b                    return a + b;
//                                           }
//   Python: def greet(name="ир"):  →  C++: void greet(std::string name = "ир")
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// ─────────────────────────────────────────────────────────────────────────────
// ТЯ: рототипы функций (Forward Declarations)
// ─────────────────────────────────────────────────────────────────────────────
//  C++ функция должна быть ЪЯ до использования.
// рототип (объявление) — говорит компилятору: «такая функция существует».
// пределение (с телом) — описывает, Т делает функция.
//
// рототип: тип_возврата имя(типы параметров);
// пределение: тип_возврата имя(параметры) { тело }
//
//  Python: порядок определения не важен (интерпретатор сначала
// читает весь файл).  C++: нужно объявить  использования!
// ─────────────────────────────────────────────────────────────────────────────

// рототипы функций (объявления):
int add(int a, int b);
double average(double a, double b);
void print_separator(char symbol = '-', int width = 40);
void greet(const std::string& name = "ир");
void swap_values(int& a, int& b);
int factorial(int n);
double power(double base, int exponent);
std::string repeat_string(const std::string& str, int times);

// ерегрузка:
int multiply(int a, int b);
double multiply(double a, double b);
int multiply(int a, int b, int c);

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   6: ункции" << std::endl;
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
    //  Python тип возврата не указывается (можно вернуть что угодно)
    //  C++ тип возврата ЯТ и С

    std::cout << "--- 1. ростые функции ---" << std::endl;

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

    print_separator();              // спользуем значения по умолчанию
    greet();                        // "ривет, ир!"
    greet("лексей");               // "ривет, лексей!"
    print_separator('=', 30);       // ==============================
    std::cout << std::endl;

    // =====================================================================
    // 3.    vs  ССЫ
    // =====================================================================
    // ередача по значению (by value):
    //   void func(int x) — создаёт . зменения внутри  влияют на оригинал.
    //
    // ередача по ссылке (by reference):
    //   void func(int& x) — работает с . зменения Ы снаружи!
    //
    // ередача по константной ссылке (by const reference):
    //   void func(const int& x) —  копирует, но  позволяет изменять.
    //   ТСЯ для больших объектов (строки, вектора и т.д.)
    //
    // Python: всё передаётся "по ссылке на объект"
    //   утабельные (list, dict) — можно изменить внутри функции
    //   ммутабельные (int, str) — нельзя изменить
    //
    // C++: Ы Я ЫТ способ передачи!
    //
    //  (learncpp.com):
    //   - ростые типы (int, double, char, bool) → по значению
    //   - Строки, вектора, объекты → по const ссылке (const std::string&)
    //   - сли нужно изменить → по ссылке (int& x)

    std::cout << "--- 3. ередача по значению vs по ссылке ---" << std::endl;

    int x{10}, y{20};
    std::cout << "о swap: x = " << x << ", y = " << y << std::endl;
    swap_values(x, y);  // ередача по ссылке — изменяет оригинал!
    std::cout << "осле swap: x = " << x << ", y = " << y << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 4. Я  
    // =====================================================================
    // ак и в Python, параметры могут иметь значения по умолчанию.
    // : араметры со значениями по умолчанию должны идти С!
    //
    // Python: def greet(name="ир"):
    // C++:    void greet(const std::string& name = "ир")
    //
    // : значения по умолчанию указываются в ЪЯ (прототипе),
    //          а  в определении (если они разделены).

    std::cout << "--- 4. начения по умолчанию ---" << std::endl;

    print_separator();            // '-' и 40
    print_separator('*');         // '*' и 40
    print_separator('=', 20);    // '=' и 20
    std::cout << std::endl;

    // =====================================================================
    // 5.   (OVERLOADING)
    // =====================================================================
    //  C++ можно создать СЬ функций с Ы именем,
    // но Ы параметрами! омпилятор выберет нужную по аргументам.
    //
    // Python: ет перегрузки! ожно использовать *args, **kwargs.
    // C++:    int multiply(int, int)
    //         double multiply(double, double)
    //         int multiply(int, int, int)

    std::cout << "--- 5. ерегрузка функций ---" << std::endl;

    std::cout << "multiply(3, 4) = " << multiply(3, 4) << std::endl;
    std::cout << "multiply(2.5, 3.0) = " << multiply(2.5, 3.0) << std::endl;
    std::cout << "multiply(2, 3, 4) = " << multiply(2, 3, 4) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 6. СЯ
    // =====================================================================
    // ункция вызывает С СЯ. ужен BASE CASE (условие выхода)!
    //
    // :  C++ нет ограничения глубины рекурсии (как в Python,
    // где по умолчанию ~1000). о стек памяти ограничен → Stack Overflow!
    //
    // Python: sys.setrecursionlimit(10000)
    // C++:    ограничен размером стека (обычно 1-8 )

    std::cout << "--- 6. екурсия ---" << std::endl;

    std::cout << "5! = " << factorial(5) << std::endl;
    std::cout << "10! = " << factorial(10) << std::endl;
    std::cout << "2^10 = " << power(2.0, 10) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 7.  С СТ  Т
    // =====================================================================
    std::cout << "--- 7. ункции со строками ---" << std::endl;

    std::string repeated = repeat_string("Ha", 3);
    std::cout << "repeat_string(\"Ha\", 3) = '" << repeated << "'" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 8. Я-ЫЯ (C++11)
    // =====================================================================
    // ямбда — анонимная функция, определённая прямо в коде.
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

    std::cout << "--- 8. ямбда-выражения ---" << std::endl;

    // ростая лямбда:
    auto add_lambda = [](int a, int b) { return a + b; };
    std::cout << "add_lambda(3, 7) = " << add_lambda(3, 7) << std::endl;

    // ямбда с захватом:
    int multiplier{3};
    auto times_n = [multiplier](int x) { return x * multiplier; };
    std::cout << "times_3(5) = " << times_n(5) << std::endl;

    // ямбда с захватом по ссылке:
    int total{0};
    auto accumulate = [&total](int x) { total += x; };
    accumulate(10);
    accumulate(20);
    accumulate(30);
    std::cout << "total после accumulate(10,20,30) = " << total << std::endl;

    // ямбда с вектором:
    std::vector<int> nums{5, 2, 8, 1, 9, 3};
    std::cout << "ётные числа: ";
    for (const auto& n : nums) {
        auto is_even = [](int x) { return x % 2 == 0; };
        if (is_even(n)) {
            std::cout << n << " ";
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  рок 6 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. апишите функцию is_prime(int n) → bool" << std::endl;
    std::cout << "2. апишите функцию fibonacci(int n) → вектор чисел" << std::endl;
    std::cout << "3. апишите перегруженную функцию max для int, double, string" << std::endl;
    std::cout << "4. еализуйте бинарный поиск рекурсивно" << std::endl;
    std::cout << "5. спользуйте лямбду для сортировки вектора строк по длине" << std::endl;

    return 0;
}

// ═══════════════════════════════════════════════════════════════════════════════
// Я  (после main)
// ═══════════════════════════════════════════════════════════════════════════════

int add(int a, int b) {
    return a + b;
}

double average(double a, double b) {
    return (a + b) / 2.0;
}

// начения по умолчанию — только в прототипе!
void print_separator(char symbol, int width) {
    for (int i{0}; i < width; ++i) {
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void greet(const std::string& name) {
    std::cout << "ривет, " << name << "!" << std::endl;
}

void swap_values(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int factorial(int n) {
    if (n <= 1) return 1;       // Base case
    return n * factorial(n - 1); // екурсивный вызов
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

// ерегруженные функции:
int multiply(int a, int b) {
    return a * b;
}

double multiply(double a, double b) {
    return a * b;
}

int multiply(int a, int b, int c) {
    return a * b * c;
}