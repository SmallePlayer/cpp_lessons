// =============================================================================
//  11: Обработка ошибок и Исключения
// =============================================================================
// Темы:
//   - Зачем нужна обработка ошибок
//   - try / catch / throw
//   - Стандартные исключения (std::exception)
//   - Создание собственных исключений
//   - noexcept (C++11)
//   - RAII — ресурсы и исключения
//   - Коды ошибок vs исключения
//   - std::optional (C++17)
//   - Лучшие практики
//
// Аналогия с Python:
//   Python: try / except / raise / finally
//   C++:    try / catch  / throw  (finally нет! Используйте RAII)
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
// ТЯ: Исключения в C++
// ─────────────────────────────────────────────────────────────────────────────
//
// Исключение — это механизм обработки ошибок, который:
// 1. Отделяет нормальный код и код обработки ошибок
// 2. Передаёт ошибку вверх по стеку вызовов
// 3. Не может быть проигнорирован (в отличие от кодов ошибок)
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
// Функция с исключением
// =====================================================================

double safe_divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Деление на ноль!");
    }
    return a / b;
}

int safe_element(const std::vector<int>& vec, int index) {
    if (index < 0 || index >= static_cast<int>(vec.size())) {
        throw std::out_of_range(
            "Индекс " + std::to_string(index) +
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
        : std::runtime_error("Недостаточно средств: запрошено " +
                             std::to_string(req) + ", доступно " +
                             std::to_string(avail)),
          requested(req), available(avail) {}

    double get_requested() const { return requested; }
    double get_available() const { return available; }
    double get_deficit() const { return requested - available; }
};

// =====================================================================
// Класс с исключениями
// =====================================================================

class SafeAccount {
private:
    std::string owner;
    double balance;

public:
    SafeAccount(const std::string& o, double initial)
        : owner(o), balance(initial) {
        if (initial < 0) {
            throw std::invalid_argument("Начальный баланс не может быть отрицательным!");
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
        return std::nullopt;  // "Нет значения"
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
    return a + b;  // Гарантированно не бросает исключений
}

// =====================================================================
// MAIN
// =====================================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   11: Обработка ошибок" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =====================================================================
    // 1. Ы try / catch
    // =====================================================================
    std::cout << "--- 1. try / catch ---" << std::endl;

    try {
        double result = safe_divide(10.0, 3.0);
        std::cout << "10 / 3 = " << result << std::endl;

        result = safe_divide(10.0, 0.0);  // Бросит исключение!
        std::cout << "Эта строка не выполнится!" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    std::cout << "Программа продолжает работать после catch!" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 2. СЬ CATCH-
    // =====================================================================
    std::cout << "--- 2. Несколько catch ---" << std::endl;

    std::vector<int> numbers{10, 20, 30, 40, 50};

    // Попробуем разные ошибки:
    for (int idx : {2, 10, -1}) {
        try {
            int val = safe_element(numbers, idx);
            std::cout << "numbers[" << idx << "] = " << val << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Общая ошибка: " << e.what() << std::endl;
        }
        catch (...) {
            // catch (...) — ловит все исключения (включая не-std)
            std::cout << "Неизвестная ошибка!" << std::endl;
        }
    }
    std::cout << std::endl;

    // =====================================================================
    // 3. ССТЫ СЯ
    // =====================================================================
    std::cout << "--- 3. Пользовательские исключения ---" << std::endl;

    try {
        SafeAccount acc{"Алексей", 1000.0};
        std::cout << "Баланс: " << acc.get_balance() << std::endl;

        acc.deposit(500.0);
        std::cout << "После депозита 500: " << acc.get_balance() << std::endl;

        acc.withdraw(2000.0);  // Бросит InsufficientFundsError!
    }
    catch (const InsufficientFundsError& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        std::cout << "  Не хватает: " << e.get_deficit() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Неверный аргумент: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    // =====================================================================
    // 4. RAII — есурсы и исключения
    // =====================================================================
    // RAII (Resource Acquisition Is Initialization):
    // Ресурс захватывается в конструкторе, освобождается в деструкторе.
    //
    // Python: with open("file") as f:  (context manager)
    // C++:    { std::ifstream file("name"); }  // RAII — файл закроется сам!
    //
    // RAII заменяет finally из Python!
    //  В C++ нет finally, потому что RAII делает его ненужным.
    //
    // Примеры RAII:
    //   std::string     — автоматически освобождает строку
    //   std::vector     — автоматически освобождает массив
    //   std::unique_ptr — автоматически вызывает delete
    //   std::fstream    — автоматически закрывает файл

    std::cout << "--- 4. RAII ---" << std::endl;
    std::cout << "RAII гарантирует освобождение ресурсов при исключениях!" << std::endl;

    try {
        auto ptr = std::make_unique<int>(42);
        std::cout << "unique_ptr создан: " << *ptr << std::endl;
        // Даже если здесь будет исключение,
        // unique_ptr освободит память автоматически!
        // throw std::runtime_error("тест");
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
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
    // Используйте optional когда:
    // - "Нет значения" — это нормальная ситуация, не ошибка
    // - Не хотите бросать исключение
    //
    // Используйте исключения когда:
    // - Произошла настоящая ошибка, которую нельзя игнорировать

    std::cout << "--- 5. std::optional ---" << std::endl;

    // safe_sqrt:
    auto result1 = safe_sqrt(16.0);
    auto result2 = safe_sqrt(-4.0);

    if (result1.has_value()) {
        std::cout << "sqrt(16) = " << result1.value() << std::endl;
    }
    // Или короче с value_or:
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
    std::cout << "--- 6. Лучшие практики ---" << std::endl;

    std::cout << "1. Бросайте по значению, ловите по const ссылке" << std::endl;
    std::cout << "   throw MyError(...); catch (const MyError& e)" << std::endl;
    std::cout << "2. Используйте RAII для управления ресурсами" << std::endl;
    std::cout << "3. Не используйте исключения для нормального потока" << std::endl;
    std::cout << "4. Наследуйте от std::exception или его потомков" << std::endl;
    std::cout << "5. Используйте noexcept для функций, которые не бросают" << std::endl;
    std::cout << "6. Используйте optional для 'может не быть значения'" << std::endl;
    std::cout << "7. Деструкторы не должны бросать исключения!" << std::endl;
    std::cout << std::endl;

    // Демонстрация noexcept:
    std::cout << "noexcept: safe_add(3, 4) = " << safe_add(3, 4) << std::endl;
    std::cout << "safe_add is noexcept: " << std::boolalpha
              << noexcept(safe_add(1, 2)) << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 11 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. Создайте класс SafeArray с проверкой границ" << std::endl;
    std::cout << "2. Реализуйте парсер чисел с обработкой ошибок" << std::endl;
    std::cout << "3. Напишите функцию чтения файла с исключениями" << std::endl;
    std::cout << "4. Создайте иерархию исключений для калькулятора" << std::endl;
    std::cout << "5. Перепишите SafeAccount с использованием optional" << std::endl;

    return 0;
}