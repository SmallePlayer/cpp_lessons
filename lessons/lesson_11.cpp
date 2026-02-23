// =============================================================================
//  11: бработка ошибок и сключения
// =============================================================================
// Темы:
//   - ачем нужна обработка ошибок
//   - try / catch / throw
//   - Стандартные исключения (std::exception)
//   - Создание собственных исключений
//   - noexcept (C++11)
//   - RAII — ресурсы и исключения
//   - оды ошибок vs исключения
//   - std::optional (C++17)
//   - учшие практики
//
// налогия с Python:
//   Python: try / except / raise / finally
//   C++:    try / catch  / throw  (finally нет! спользуйте RAII)
//
//   Python: raise ValueError("сообщение")
//   C++:    throw std::invalid_argument("сообщение");
//
//   Python: except Exception as e:
//   C++:    catch (const std::exception& e) { e.what(); }
// =============================================================================

#include <iostream>
#include <stdexcept>    // runtime_error, invalid_argument, out_of_range, etc.
#include <string>
#include <vector>
#include <optional>
#include <cmath>     // std::optional (C++17)
#include <fstream>      // файловые потоки
#include <memory>

// ─────────────────────────────────────────────────────────────────────────────
// ТЯ: сключения в C++
// ─────────────────────────────────────────────────────────────────────────────
//
// сключение — это механизм обработки ошибок, который:
// 1. ЯТ нормальный код и код обработки ошибок
// 2. Т ошибку вверх по стеку вызовов
// 3.  Т быть проигнорирован (в отличие от кодов ошибок)
//
// throw — бросает исключение (как raise в Python)
// try   — блок, в котором может возникнуть исключение
// catch — обработчик исключения (как except в Python)
//
// Стандартная иерархия исключений:
//   std::exception (базовый)
//   ├── std::logic_error
//   │   ├── std::invalid_argument
//   │   ├── std::out_of_range
//   │   └── std::domain_error
//   ├── std::runtime_error
//   │   ├── std::overflow_error
//   │   ├── std::underflow_error
//   │   └── std::range_error
//   └── std::bad_alloc (нет памяти)
// ─────────────────────────────────────────────────────────────────────────────

// =====================================================================
// ункция с исключением
// =====================================================================

double safe_divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("еление на ноль!");
    }
    return a / b;
}

int safe_element(const std::vector<int>& vec, int index) {
    if (index < 0 || index >= static_cast<int>(vec.size())) {
        throw std::out_of_range(
            "ндекс " + std::to_string(index) +
            " вне диапазона [0, " + std::to_string(vec.size() - 1) + "]"
        );
    }
    return vec[static_cast<std::size_t>(index)];
}

// =====================================================================
// Собственное исключение
// =====================================================================

class InsufficientFundsError : public std::runtime_error {
private:
    double requested;
    double available;

public:
    InsufficientFundsError(double req, double avail)
        : std::runtime_error("едостаточно средств: запрошено " +
                             std::to_string(req) + ", доступно " +
                             std::to_string(avail)),
          requested(req), available(avail) {}

    double get_requested() const { return requested; }
    double get_available() const { return available; }
    double get_deficit() const { return requested - available; }
};

// =====================================================================
// ласс с исключениями
// =====================================================================

class SafeAccount {
private:
    std::string owner;
    double balance;

public:
    SafeAccount(const std::string& o, double initial)
        : owner(o), balance(initial) {
        if (initial < 0) {
            throw std::invalid_argument("ачальный баланс не может быть отрицательным!");
        }
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма депозита должна быть положительной!");
        }
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма снятия должна быть положительной!");
        }
        if (amount > balance) {
            throw InsufficientFundsError(amount, balance);
        }
        balance -= amount;
    }

    double get_balance() const { return balance; }
    const std::string& get_owner() const { return owner; }
};

// =====================================================================
// std::optional — безопасная альтернатива (C++17)
// =====================================================================

std::optional<double> safe_sqrt(double x) {
    if (x < 0.0) {
        return std::nullopt;  // "ет значения"
    }
    return std::sqrt(x);
}

std::optional<int> find_in_vector(const std::vector<int>& vec, int target) {
    for (std::size_t i{0}; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return static_cast<int>(i);
        }
    }
    return std::nullopt;
}

// =====================================================================
// noexcept — обещание не бросать исключений
// =====================================================================

int safe_add(int a, int b) noexcept {
    return a + b;  // арантированно не бросает исключений
}

// =====================================================================
// MAIN
// =====================================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   11: бработка ошибок" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =====================================================================
    // 1. Ы try / catch
    // =====================================================================
    std::cout << "--- 1. try / catch ---" << std::endl;

    try {
        double result = safe_divide(10.0, 3.0);
        std::cout << "10 / 3 = " << result << std::endl;

        result = safe_divide(10.0, 0.0);  // росит исключение!
        std::cout << "та строка  выполнится!" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "шибка: " << e.what() << std::endl;
    }
    std::cout << "рограмма продолжает работать после catch!" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 2. СЬ CATCH-
    // =====================================================================
    std::cout << "--- 2. есколько catch ---" << std::endl;

    std::vector<int> numbers{10, 20, 30, 40, 50};

    // опробуем разные ошибки:
    for (int idx : {2, 10, -1}) {
        try {
            int val = safe_element(numbers, idx);
            std::cout << "numbers[" << idx << "] = " << val << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cout << "шибка: " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "бщая ошибка: " << e.what() << std::endl;
        }
        catch (...) {
            // catch (...) — ловит С исключения (включая не-std)
            std::cout << "еизвестная ошибка!" << std::endl;
        }
    }
    std::cout << std::endl;

    // =====================================================================
    // 3. ССТЫ СЯ
    // =====================================================================
    std::cout << "--- 3. ользовательские исключения ---" << std::endl;

    try {
        SafeAccount acc{"лексей", 1000.0};
        std::cout << "аланс: " << acc.get_balance() << std::endl;

        acc.deposit(500.0);
        std::cout << "осле депозита 500: " << acc.get_balance() << std::endl;

        acc.withdraw(2000.0);  // росит InsufficientFundsError!
    }
    catch (const InsufficientFundsError& e) {
        std::cout << "шибка: " << e.what() << std::endl;
        std::cout << "  е хватает: " << e.get_deficit() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "еверный аргумент: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    // =====================================================================
    // 4. RAII — есурсы и исключения
    // =====================================================================
    // RAII (Resource Acquisition Is Initialization):
    // есурс захватывается в конструкторе, освобождается в деструкторе.
    //
    // Python: with open("file") as f:  (context manager)
    // C++:    { std::ifstream file("name"); }  // RAII — файл закроется сам!
    //
    // RAII заменяет finally из Python!
    //  C++ Т finally, потому что RAII делает его ненужным.
    //
    // римеры RAII:
    //   std::string     — автоматически освобождает строку
    //   std::vector     — автоматически освобождает массив
    //   std::unique_ptr — автоматически вызывает delete
    //   std::fstream    — автоматически закрывает файл

    std::cout << "--- 4. RAII ---" << std::endl;
    std::cout << "RAII гарантирует освобождение ресурсов при исключениях!" << std::endl;

    try {
        auto ptr = std::make_unique<int>(42);
        std::cout << "unique_ptr создан: " << *ptr << std::endl;
        // аже если здесь будет исключение,
        // unique_ptr освободит память автоматически!
        // throw std::runtime_error("тест");
    }
    catch (const std::exception& e) {
        std::cout << "шибка: " << e.what() << std::endl;
    }
    // ptr уничтожен, память освобождена — даже при исключении!
    std::cout << std::endl;

    // =====================================================================
    // 5. std::optional (C++17) — ЬТТ СЯ
    // =====================================================================
    // std::optional<T> — может содержать значение T или "ничего" (nullopt).
    //
    // Python: Optional[float] (typing) или возврат None
    // C++:    std::optional<double>
    //
    // спользуйте optional когда:
    // - "ет значения" — это ЬЯ ситуация,  ошибка
    // - е хотите бросать исключение
    //
    // спользуйте исключения когда:
    // - роизошла СТЯЩЯ ошибка, которую нельзя игнорировать

    std::cout << "--- 5. std::optional ---" << std::endl;

    // safe_sqrt:
    auto result1 = safe_sqrt(16.0);
    auto result2 = safe_sqrt(-4.0);

    if (result1.has_value()) {
        std::cout << "sqrt(16) = " << result1.value() << std::endl;
    }
    // ли короче с value_or:
    std::cout << "sqrt(16) = " << result1.value_or(0.0) << std::endl;

    if (result2.has_value()) {
        std::cout << "sqrt(-4) = " << result2.value() << std::endl;
    } else {
        std::cout << "sqrt(-4) = нет значения (отрицательное число)" << std::endl;
    }

    // find_in_vector:
    std::vector<int> data{10, 20, 30, 40, 50};

    auto pos1 = find_in_vector(data, 30);
    auto pos2 = find_in_vector(data, 99);

    if (pos1) {  // operator bool() — есть ли значение
        std::cout << "30 найдено на позиции " << *pos1 << std::endl;
    }
    if (!pos2) {
        std::cout << "99 не найдено" << std::endl;
    }
    std::cout << std::endl;

    // =====================================================================
    // 6. Ш Т
    // =====================================================================
    std::cout << "--- 6. учшие практики ---" << std::endl;

    std::cout << "1. росайте по значению, ловите по const ссылке" << std::endl;
    std::cout << "   throw MyError(...); catch (const MyError& e)" << std::endl;
    std::cout << "2. спользуйте RAII для управления ресурсами" << std::endl;
    std::cout << "3. е используйте исключения для нормального потока" << std::endl;
    std::cout << "4. аследуйте от std::exception или его потомков" << std::endl;
    std::cout << "5. спользуйте noexcept для функций, которые не бросают" << std::endl;
    std::cout << "6. спользуйте optional для 'может не быть значения'" << std::endl;
    std::cout << "7. еструкторы  не должны бросать исключения!" << std::endl;
    std::cout << std::endl;

    // емонстрация noexcept:
    std::cout << "noexcept: safe_add(3, 4) = " << safe_add(3, 4) << std::endl;
    std::cout << "safe_add is noexcept: " << std::boolalpha
              << noexcept(safe_add(1, 2)) << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  рок 11 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. Создайте класс SafeArray с проверкой границ" << std::endl;
    std::cout << "2. еализуйте парсер чисел с обработкой ошибок" << std::endl;
    std::cout << "3. апишите функцию чтения файла с исключениями" << std::endl;
    std::cout << "4. Создайте иерархию исключений для калькулятора" << std::endl;
    std::cout << "5. ерепишите SafeAccount с использованием optional" << std::endl;

    return 0;
}