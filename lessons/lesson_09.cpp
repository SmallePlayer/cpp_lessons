// =============================================================================
//  9: Структуры и Классы (ООП — Часть 1)
// =============================================================================
// Темы:
//   - struct — группировка данных
//   - class — данные + поведение
//   - Модификаторы доступа: public, private, protected
//   - Конструкторы и деструкторы
//   - Список инициализации членов
//   - Методы класса
//   - this — указатель на текущий объект
//   - Перегрузка операторов
//   - Статические члены
//
// Аналогия с Python:
//   Python: class Person:
//               def __init__(self, name, age):
//                   self.name = name
//                   self.age = age
//   C++:    class Person {
//               std::string name;
//               int age;
//           public:
//               Person(std::string n, int a) : name(n), age(a) {}
//           };
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// ─────────────────────────────────────────────────────────────────────────────
// ТЯ: struct vs class
// ─────────────────────────────────────────────────────────────────────────────
// struct и class в C++ почти одинаковы!
// Единственная разница:
//   struct — члены по умолчанию PUBLIC
//   class  — члены по умолчанию PRIVATE
//
// Соглашение:
//   struct — для простых структур данных (POD — Plain Old Data)
//   class  — для объектов с поведением (методами)
// ─────────────────────────────────────────────────────────────────────────────

// =====================================================================
// 1. struct — СТЯ СТТ ЫХ
// =====================================================================
// Группирует несколько переменных в один тип.
// Python аналогия: dataclass или namedtuple
//   @dataclass
//   class Point:
//       x: float
//       y: float

struct Point {
    double x;
    double y;

    // Метод в структуре (вполне допустимо):
    double distance_to(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

// Структура с конструктором:
struct Color {
    int r, g, b;

    Color() : r(0), g(0), b(0) {}  // Конструктор по умолчанию
    Color(int red, int green, int blue) : r(red), g(green), b(blue) {}

    void print() const {
        std::cout << "RGB(" << r << ", " << g << ", " << b << ")";
    }
};

// =====================================================================
// 2. class — Ы СС С СЯ
// =====================================================================

class BankAccount {
// private: — по умолчанию для class
private:
    std::string owner;
    double balance;
    int account_id;
    static int next_id;  // Статический счётчик

public:
    // ─── Конструкторы ───
    // Конструктор — специальная функция, вызывается при создании объекта.
    // Имя = имя класса. Нет возвращаемого типа.
    //
    // Python: def __init__(self, ...):
    // C++:    ClassName(параметры) : инициализация { тело }
    //
    // Список инициализации членов (member initializer list):
    //   BankAccount(std::string o) : owner(o), balance(0.0) { }
    //   Это лучше, чем присваивание в теле конструктора!
    //   Поля инициализируются до выполнения тела конструктора.

    // Конструктор по умолчанию:
    BankAccount() : owner("Unknown"), balance(0.0), account_id(next_id++) {
        std::cout << "  [Конструктор] Создан аккаунт #" << account_id << std::endl;
    }

    // Параметризированный конструктор:
    BankAccount(const std::string& o, double b)
        : owner(o), balance(b), account_id(next_id++) {
        std::cout << "  [Конструктор] Создан аккаунт #" << account_id
                  << " для " << owner << std::endl;
    }

    // ─── Деструктор ───
    // Вызывается при уничтожении объекта (выход из scope, delete).
    // Используется для освобождения ресурсов.
    //
    // Python: def __del__(self):
    // C++:    ~ClassName() { }
    ~BankAccount() {
        std::cout << "  [Деструктор] Аккаунт #" << account_id
                  << " (" << owner << ") уничтожен" << std::endl;
    }

    // ─── Методы ───
    // const после метода = метод  изменяет объект
    //
    // Python: def get_balance(self):  →  C++: double get_balance() const;
    //         self.balance                     this->balance  (или просто balance)

    double get_balance() const { return balance; }
    const std::string& get_owner() const { return owner; }
    int get_id() const { return account_id; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "  +" << amount << " → баланс: " << balance << std::endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "  -" << amount << " → баланс: " << balance << std::endl;
            return true;
        }
        std::cout << "  Недостаточно средств!" << std::endl;
        return false;
    }

    void print_info() const {
        std::cout << "  Аккаунт #" << account_id << " | "
                  << owner << " | Баланс: " << balance << std::endl;
    }

    // Статический метод:
    static int get_total_accounts() { return next_id; }
};

// Инициализация статического члена (должна быть вне класса!):
int BankAccount::next_id = 1;

// =====================================================================
// 3.  Т
// =====================================================================

class Vector2D {
private:
    double x, y;

public:
    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    double get_x() const { return x; }
    double get_y() const { return y; }
    double length() const { return std::sqrt(x * x + y * y); }

    // Перегрузка оператора +
    // Python: def __add__(self, other):
    // C++:    Vector2D operator+(const Vector2D& other) const
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // Перегрузка оператора -
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // Перегрузка оператора * (скаляр)
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // Перегрузка оператора ==
    bool operator==(const Vector2D& other) const {
        return x == other.x && y == other.y;
    }

    // Перегрузка оператора << для вывода (friend функция)
    // Python: def __str__(self):  или  def __repr__(self):
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "Vector2D(" << v.x << ", " << v.y << ")";
        return os;
    }
};

// =====================================================================
// MAIN
// =====================================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   9: Структуры и Классы" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // --- 1. struct ---
    std::cout << "--- 1. Структуры (struct) ---" << std::endl;

    Point p1{3.0, 4.0};
    Point p2{6.0, 8.0};
    std::cout << "p1 = (" << p1.x << ", " << p1.y << ")" << std::endl;
    std::cout << "p2 = (" << p2.x << ", " << p2.y << ")" << std::endl;
    std::cout << "Расстояние: " << p1.distance_to(p2) << std::endl;

    // Aggregate initialization:
    Point p3 = {0.0, 0.0};
    std::cout << "p3 = (" << p3.x << ", " << p3.y << ")" << std::endl;

    Color red{255, 0, 0};
    Color white;  // Конструктор по умолчанию
    std::cout << "red = "; red.print(); std::cout << std::endl;
    std::cout << "white = "; white.print(); std::cout << std::endl;
    std::cout << std::endl;

    // --- 2. class ---
    std::cout << "--- 2. Классы (class) ---" << std::endl;
    {
        BankAccount acc1;
        BankAccount acc2{"Алексей", 1000.0};

        acc2.print_info();
        acc2.deposit(500.0);
        acc2.withdraw(200.0);
        acc2.withdraw(2000.0);  // Недостаточно средств
        acc2.print_info();

        std::cout << "Всего аккаунтов создано: " << BankAccount::get_total_accounts() << std::endl;
        std::cout << std::endl;
    }  // acc1 и acc2 уничтожаются — вызываются деструкторы!
    std::cout << std::endl;

    // --- 3. ерегрузка операторов ---
    std::cout << "--- 3. Перегрузка операторов ---" << std::endl;

    Vector2D v1{3.0, 4.0};
    Vector2D v2{1.0, 2.0};

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v1 + v2 = " << (v1 + v2) << std::endl;
    std::cout << "v1 - v2 = " << (v1 - v2) << std::endl;
    std::cout << "v1 * 2 = " << (v1 * 2.0) << std::endl;
    std::cout << "v1.length() = " << v1.length() << std::endl;
    std::cout << "v1 == v2: " << std::boolalpha << (v1 == v2) << std::endl;
    std::cout << "v1 == v1: " << std::boolalpha << (v1 == v1) << std::endl;
    std::cout << std::endl;

    // --- 4. ассив объектов ---
    std::cout << "--- 4. Вектор объектов ---" << std::endl;

    std::vector<Point> points = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    Point origin{0.0, 0.0};

    for (const auto& p : points) {
        std::cout << "  (" << p.x << ", " << p.y << ") → расстояние от начала: "
                  << p.distance_to(origin) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 9 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. Создайте класс Rectangle с площадью и периметром" << std::endl;
    std::cout << "2. Создайте класс Student с оценками и средним баллом" << std::endl;
    std::cout << "3. Перегрузите оператор [] для класса Matrix" << std::endl;
    std::cout << "4. Реализуйте класс String с конструктором копирования" << std::endl;
    std::cout << "5. Создайте класс Stack с методами push/pop/top" << std::endl;

    return 0;
}