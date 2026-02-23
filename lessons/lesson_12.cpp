// =============================================================================
//  12: Шаблоны и Современный C++ (C++11/14/17/20)
// =============================================================================
// Темы:
//   - Шаблоны функций (function templates)
//   - Шаблоны классов (class templates)
//   - auto и decltype
//   - Семантика перемещения (move semantics)
//   - std::move
//   - Structured bindings (C++17)
//   - if constexpr (C++17)
//   - constexpr функции
//   - Range-based for с инициализатором
//   - бзор важных фич современного C++
//
// налогия с Python:
//   Python: def max_val(a, b): return a if a > b else b  (работает для любого типа)
//   C++:    template<typename T> T max_val(T a, T b) { return (a > b) ? a : b; }
//   Python: утиная типизация (duck typing)
//   C++:    шаблоны = "компилируемая утиная типизация"
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <type_traits>   // is_integral, is_floating_point, etc.
#include <utility>       // std::move, std::forward
#include <algorithm>
#include <numeric>

// ─────────────────────────────────────────────────────────────────────────────
// ТЯ: Шаблоны (Templates)
// ─────────────────────────────────────────────────────────────────────────────
//
// Шаблоны — это "обобщённое программирование" (generic programming).
// ы пишете код  раз, и он работает с Ы типами!
//
// омпилятор Т конкретный код для каждого используемого типа.
// то называется "инстанцирование шаблона" (template instantiation).
//
// template<typename T>   — T будет заменён на конкретный тип
// template<class T>      — то же самое (typename == class здесь)
//
// Python: не нужны — утиная типизация ("если крякает как утка...")
// C++:    нужны шаблоны для обобщённого кода!
//
// менно шаблоны лежат в основе STL:
//   std::vector<int>, std::vector<string>, std::map<string, int>
//   то всё СТЯ шаблонов!
// ─────────────────────────────────────────────────────────────────────────────

// =====================================================================
// 1. Ш 
// =====================================================================

// Шаблон максимума — работает с любым типом, поддерживающим operator>
template<typename T>
T max_val(T a, T b) {
    return (a > b) ? a : b;
}

// Шаблон обмена значений:
template<typename T>
void my_swap(T& a, T& b) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

// Шаблон вывода вектора:
template<typename T>
void print_vector(const std::vector<T>& vec, const std::string& label = "") {
    if (!label.empty()) {
        std::cout << label << ": ";
    }
    std::cout << "[";
    for (std::size_t i{0}; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i + 1 < vec.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Шаблон суммы элементов:
template<typename T>
T sum_vector(const std::vector<T>& vec) {
    T result{};  // нициализация нулём для числовых типов
    for (const auto& elem : vec) {
        result += elem;
    }
    return result;
}

// =====================================================================
// 2. Ш СС
// =====================================================================

template<typename T>
class Stack {
private:
    std::vector<T> data;

public:
    void push(const T& value) {
        data.push_back(value);
    }

    void push(T&& value) {  // еремещение!
        data.push_back(std::move(value));
    }

    T pop() {
        if (data.empty()) {
            throw std::out_of_range("Stack is empty!");
        }
        T top = std::move(data.back());
        data.pop_back();
        return top;
    }

    const T& top() const {
        if (data.empty()) {
            throw std::out_of_range("Stack is empty!");
        }
        return data.back();
    }

    bool empty() const { return data.empty(); }
    std::size_t size() const { return data.size(); }

    void print() const {
        std::cout << "Stack[";
        for (std::size_t i{0}; i < data.size(); ++i) {
            std::cout << data[i];
            if (i + 1 < data.size()) std::cout << ", ";
        }
        std::cout << "] (top →)" << std::endl;
    }
};

// =====================================================================
// 3. Ш С СЬ Т
// =====================================================================

template<typename K, typename V>
class KeyValue {
private:
    K key;
    V value;

public:
    KeyValue(const K& k, const V& v) : key(k), value(v) {}

    const K& get_key() const { return key; }
    const V& get_value() const { return value; }

    friend std::ostream& operator<<(std::ostream& os, const KeyValue& kv) {
        os << "{" << kv.key << ": " << kv.value << "}";
        return os;
    }
};

// =====================================================================
// 4. constexpr — ЫСЯ  Т Я
// =====================================================================

constexpr int constexpr_factorial(int n) {
    return (n <= 1) ? 1 : n * constexpr_factorial(n - 1);
}

constexpr double constexpr_power(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

// =====================================================================
// 5. if constexpr (C++17) — ЯЫ if
// =====================================================================

template<typename T>
std::string type_description(T value) {
    if constexpr (std::is_integral_v<T>) {
        return "елое число: " + std::to_string(value);
    } else if constexpr (std::is_floating_point_v<T>) {
        return "робное число: " + std::to_string(value);
    } else {
        return "ругой тип";
    }
}

// Специализация для string:
template<>
std::string type_description<std::string>(std::string value) {
    return "Строка: " + value;
}

// =====================================================================
// MAIN
// =====================================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   12: Шаблоны и Современный C++" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // --- 1. Шаблоны функций ---
    std::cout << "--- 1. Шаблоны функций ---" << std::endl;

    // омпилятор сам определяет T по аргументам:
    std::cout << "max_val(3, 7) = " << max_val(3, 7) << std::endl;
    std::cout << "max_val(3.14, 2.71) = " << max_val(3.14, 2.71) << std::endl;
    std::cout << "max_val('a', 'z') = " << max_val('a', 'z') << std::endl;

    // ожно указать тип явно:
    std::cout << "max_val<double>(3, 7.5) = " << max_val<double>(3, 7.5) << std::endl;

    // бмен значениями:
    int x{10}, y{20};
    std::cout << "о: x=" << x << ", y=" << y << std::endl;
    my_swap(x, y);
    std::cout << "осле my_swap: x=" << x << ", y=" << y << std::endl;
    std::cout << std::endl;

    // --- 2. Шаблон вывода вектора ---
    std::cout << "--- 2. Шаблонные функции для контейнеров ---" << std::endl;

    std::vector<int> int_vec{1, 2, 3, 4, 5};
    std::vector<double> dbl_vec{1.1, 2.2, 3.3};
    std::vector<std::string> str_vec{"hello", "world", "cpp"};

    print_vector(int_vec, "int");
    print_vector(dbl_vec, "double");
    print_vector(str_vec, "string");

    std::cout << "Сумма int_vec: " << sum_vector(int_vec) << std::endl;
    std::cout << "Сумма dbl_vec: " << sum_vector(dbl_vec) << std::endl;
    std::cout << std::endl;

    // --- 3. Шаблон класса Stack ---
    std::cout << "--- 3. Шаблон класса Stack ---" << std::endl;

    Stack<int> int_stack;
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    int_stack.print();

    std::cout << "top: " << int_stack.top() << std::endl;
    std::cout << "pop: " << int_stack.pop() << std::endl;
    int_stack.print();

    Stack<std::string> str_stack;
    str_stack.push("Hello");
    str_stack.push("World");
    str_stack.print();
    std::cout << std::endl;

    // --- 4. KeyValue ---
    std::cout << "--- 4. Шаблон с несколькими параметрами ---" << std::endl;

    KeyValue<std::string, int> kv1{"возраст", 25};
    KeyValue<int, std::string> kv2{1, "первый"};
    std::cout << kv1 << std::endl;
    std::cout << kv2 << std::endl;
    std::cout << std::endl;

    // --- 5. constexpr ---
    std::cout << "--- 5. constexpr (вычисления при компиляции) ---" << std::endl;

    constexpr int fact5 = constexpr_factorial(5);
    constexpr double pow2_8 = constexpr_power(2.0, 8);

    std::cout << "5! = " << fact5 << " (вычислено при компиляции!)" << std::endl;
    std::cout << "2^8 = " << pow2_8 << " (вычислено при компиляции!)" << std::endl;

    // ассив с constexpr размером:
    constexpr int SIZE = constexpr_factorial(4);  // 24
    std::array<int, SIZE> big_arr{};
    std::cout << "ассив размером " << SIZE << "! элементов" << std::endl;
    std::cout << std::endl;

    // --- 6. if constexpr ---
    std::cout << "--- 6. if constexpr (C++17) ---" << std::endl;

    std::cout << type_description(42) << std::endl;
    std::cout << type_description(3.14) << std::endl;
    std::cout << type_description(std::string("Hello")) << std::endl;
    std::cout << std::endl;

    // --- 7. auto и decltype ---
    std::cout << "--- 7. auto и decltype ---" << std::endl;

    auto a = 42;           // int
    auto b = 3.14;         // double
    auto c = "hello";      // const char*
    auto d = std::string("world");  // std::string

    // decltype — определяет тип выражения:
    decltype(a) e = 100;   // int (тип как у a)
    decltype(b) f = 2.71;  // double (тип как у b)

    std::cout << "auto a = 42:        " << a << std::endl;
    std::cout << "auto b = 3.14:      " << b << std::endl;
    std::cout << "auto c = \"hello\":   " << c << std::endl;
    std::cout << "auto d = string:    " << d << std::endl;
    std::cout << "decltype(a) e = 100: " << e << std::endl;
    std::cout << std::endl;

    // --- 8. Structured bindings (C++17) ---
    std::cout << "--- 8. Structured bindings ---" << std::endl;

    // С массивом:
    int arr[3] = {10, 20, 30};
    auto [first, second, third] = arr;
    std::cout << "array: " << first << ", " << second << ", " << third << std::endl;

    // С парой:
    std::pair<std::string, int> person{"лексей", 25};
    auto [name, age] = person;
    std::cout << "pair: " << name << ", " << age << std::endl;

    //  цикле с map:
    std::vector<std::pair<std::string, int>> scores = {
        {"лексей", 95}, {"ария", 88}, {"ван", 92}
    };
    for (const auto& [n, s] : scores) {
        std::cout << "  " << n << ": " << s << std::endl;
    }
    std::cout << std::endl;

    // --- 9. Move semantics (кратко) ---
    std::cout << "--- 9. Семантика перемещения ---" << std::endl;

    std::string original = "Hello, World! This is a long string for demo.";
    std::cout << "original: '" << original << "'" << std::endl;

    std::string moved = std::move(original);  // Щ, не копирование!
    std::cout << "moved:    '" << moved << "'" << std::endl;
    std::cout << "original после move: '" << original << "' (пустая!)" << std::endl;
    // : после std::move объект в "valid but unspecified state"
    // го можно присвоить заново или уничтожить, но  использовать!

    std::vector<std::string> vec;
    std::string temp = "перемещаемая строка";
    vec.push_back(std::move(temp));  // еремещение вместо копирования!
    std::cout << "vec[0]: '" << vec[0] << "'" << std::endl;
    std::cout << "temp после move: '" << temp << "'" << std::endl;
    std::cout << std::endl;

    // --- 10. бзор стандартов ---
    std::cout << "--- 10. бзор стандартов C++ ---" << std::endl;
    std::cout << "C++11: auto, range-for, лямбды, move, smart ptr, {}" << std::endl;
    std::cout << "C++14: auto return, generic лямбды, make_unique" << std::endl;
    std::cout << "C++17: optional, string_view, structured bindings," << std::endl;
    std::cout << "       if constexpr, filesystem, if с инициализацией" << std::endl;
    std::cout << "C++20: concepts, ranges, coroutines, modules," << std::endl;
    std::cout << "       std::format, <=> (spaceship operator)" << std::endl;
    std::cout << "C++23: print/println, expected, flat_map и др." << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  рок 12 завершён!" << std::endl;
    std::cout << "  Я! С  Ы!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. апишите шаблонную функцию min_element для массива" << std::endl;
    std::cout << "2. Создайте шаблонный класс Matrix<T, Rows, Cols>" << std::endl;
    std::cout << "3. еализуйте шаблонный связанный список" << std::endl;
    std::cout << "4. спользуйте constexpr для вычисления числа ибоначчи" << std::endl;
    std::cout << "5. апишите программу с использованием всех фич из уроков" << std::endl;

    return 0;
}