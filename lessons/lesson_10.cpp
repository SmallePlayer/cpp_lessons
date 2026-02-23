// =============================================================================
// Урок 10: Наследование и Полиморфизм (ООП — Часть 2)
// =============================================================================
// Темы:
//   - Наследование (inheritance)
//   - Модификаторы доступа при наследовании
//   - Виртуальные функции (virtual)
//   - Полиморфизм — ключевая концепция ООП
//   - override и final (C++11)
//   - Абстрактные классы (чисто виртуальные функции)
//   - Множественное наследование
//   - dynamic_cast
//
// Аналогия с Python:
//   Python: class Dog(Animal):            →  C++: class Dog : public Animal {
//   Python: def speak(self): (override)   →  C++: void speak() override;
//   Python: @abstractmethod               →  C++: virtual void f() = 0;
//   Python: class C(A, B):               →  C++: class C : public A, public B {
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

// ─────────────────────────────────────────────────────────────────────────────
// ТЕМА: Наследование
// ─────────────────────────────────────────────────────────────────────────────
// Наследование позволяет создавать новые классы на основе существующих.
//
// Базовый класс (base/parent)  — от которого наследуют
// Производный класс (derived/child) — который наследует
//
// class Derived : public Base {
//     // Derived имеет ВСЕ члены Base + свои собственные
// };
//
// Модификаторы наследования:
//   public    — public остаётся public, protected остаётся protected
//   protected — public → protected, protected → protected
//   private   — всё становится private
//
// ВСЕГДА используйте public наследование!
// ─────────────────────────────────────────────────────────────────────────────

// =====================================================================
// 1. БАЗОВЫЙ КЛАСС: Shape (Фигура)
// =====================================================================

class Shape {
protected:           // protected — доступно в наследниках, но не снаружи
    std::string name;
    std::string color;

public:
    Shape(const std::string& n, const std::string& c = "белый")
        : name(n), color(c) {
        std::cout << "  [Shape] Создана фигура: " << name << std::endl;
    }

    virtual ~Shape() {
        // Виртуальный деструктор — ОБЯЗАТЕЛЕН для базовых классов!
        // Без него delete для указателя на базовый класс НЕ вызовет
        // деструктор наследника → утечка ресурсов!
        std::cout << "  [~Shape] Удалена фигура: " << name << std::endl;
    }

    // ─── ВИРТУАЛЬНЫЕ МЕТОДЫ ───
    // virtual — функция может быть ПЕРЕОПРЕДЕЛЕНА в наследнике.
    // Вызывается правильная версия в зависимости от РЕАЛЬНОГО типа объекта.
    //
    // БЕЗ virtual: вызывается версия по типу УКАЗАТЕЛЯ (статическая привязка)
    // С virtual:   вызывается версия по типу ОБЪЕКТА (динамическая привязка)
    //
    // Python: ВСЕ методы виртуальные по умолчанию!
    // C++:    Нужно ЯВНО указать virtual!

    virtual double area() const = 0;          // = 0 → ЧИСТО виртуальная (абстрактная)
    virtual double perimeter() const = 0;     // Наследники ОБЯЗАНЫ реализовать!

    virtual void describe() const {
        std::cout << "  Фигура: " << name << ", цвет: " << color << std::endl;
    }

    const std::string& get_name() const { return name; }
};

// =====================================================================
// 2. НАСЛЕДНИК: Circle (Круг)
// =====================================================================

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r, const std::string& c = "красный")
        : Shape("Круг", c), radius(r) {}

    // override (C++11) — явно указывает, что мы переопределяем виртуальную функцию.
    // Если в базовом классе нет такой виртуальной функции — ОШИБКА компиляции!
    // Это защита от опечаток.
    double area() const override {
        return 3.14159265358979323846 * radius * radius;
    }

    double perimeter() const override {
        return 2.0 * 3.14159265358979323846 * radius;
    }

    void describe() const override {
        Shape::describe();  // Вызов метода БАЗОВОГО класса
        std::cout << "  Радиус: " << radius << ", Площадь: " << area() << std::endl;
    }

    double get_radius() const { return radius; }
};

// =====================================================================
// 3. НАСЛЕДНИК: Rectangle (Прямоугольник)
// =====================================================================

class Rectangle : public Shape {
protected:
    double width, height;

public:
    Rectangle(double w, double h, const std::string& c = "синий")
        : Shape("Прямоугольник", c), width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2.0 * (width + height);
    }

    void describe() const override {
        Shape::describe();
        std::cout << "  " << width << " x " << height
                  << ", Площадь: " << area() << std::endl;
    }
};

// =====================================================================
// 4. НАСЛЕДНИК НАСЛЕДНИКА: Square (Квадрат от Прямоугольника)
// =====================================================================

class Square : public Rectangle {
public:
    // final (C++11) — запрещает дальнейшее наследование или переопределение
    Square(double side, const std::string& c = "зелёный")
        : Rectangle(side, side, c) {
        name = "Квадрат";  // Изменяем protected поле базового класса
    }

    void describe() const override final {  // final — нельзя переопределить далее
        Shape::describe();
        std::cout << "  Сторона: " << width << ", Площадь: " << area() << std::endl;
    }
};

// =====================================================================
// 5. НАСЛЕДНИК: Triangle (Треугольник)
// =====================================================================

class Triangle : public Shape {
private:
    double a, b, c_side;

public:
    Triangle(double a, double b, double c, const std::string& col = "жёлтый")
        : Shape("Треугольник", col), a(a), b(b), c_side(c) {}

    double area() const override {
        // Формула Герона:
        double s = (a + b + c_side) / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c_side));
    }

    double perimeter() const override {
        return a + b + c_side;
    }
};

// =====================================================================
// 6. ИНТЕРФЕЙСЫ (чисто абстрактный класс)
// =====================================================================
// Класс, где ВСЕ методы = 0 (чисто виртуальные).
// Нельзя создать экземпляр!
// Python аналогия: abc.ABC с @abstractmethod

class Printable {
public:
    virtual ~Printable() = default;
    virtual std::string to_string() const = 0;
    virtual void print() const {
        std::cout << to_string() << std::endl;
    }
};

class Serializable {
public:
    virtual ~Serializable() = default;
    virtual std::string serialize() const = 0;
};

// Множественное наследование: наследуем от двух интерфейсов
class Document : public Printable, public Serializable {
private:
    std::string title;
    std::string content;

public:
    Document(const std::string& t, const std::string& c)
        : title(t), content(c) {}

    std::string to_string() const override {
        return "[" + title + "] " + content;
    }

    std::string serialize() const override {
        return "{\"title\":\"" + title + "\",\"content\":\"" + content + "\"}";
    }
};

// =====================================================================
// MAIN
// =====================================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Урок 10: Наследование и Полиморфизм" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // --- 1. Создание объектов ---
    std::cout << "--- 1. Создание фигур ---" << std::endl;

    Circle circle{5.0};
    Rectangle rect{4.0, 6.0};
    Square square{3.0};
    Triangle tri{3.0, 4.0, 5.0};
    std::cout << std::endl;

    // --- 2. Вызов методов ---
    std::cout << "--- 2. Методы объектов ---" << std::endl;
    circle.describe();
    std::cout << std::endl;
    rect.describe();
    std::cout << std::endl;
    square.describe();
    std::cout << std::endl;

    // --- 3. ПОЛИМОРФИЗМ — главная сила ООП! ---
    std::cout << "--- 3. Полиморфизм ---" << std::endl;

    // Вектор указателей на БАЗОВЫЙ класс, но содержит РАЗНЫЕ объекты!
    // Вызывается ПРАВИЛЬНЫЙ метод для каждого объекта!
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Square>(3.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));

    std::cout << "\nВсе фигуры (полиморфный вызов):" << std::endl;
    for (const auto& shape : shapes) {
        std::cout << "  " << shape->get_name()
                  << ": площадь = " << shape->area()
                  << ", периметр = " << shape->perimeter() << std::endl;
    }
    std::cout << std::endl;

    // Суммарная площадь всех фигур:
    double total_area{0.0};
    for (const auto& shape : shapes) {
        total_area += shape->area();
    }
    std::cout << "Суммарная площадь: " << total_area << std::endl;
    std::cout << std::endl;

    // --- 4. dynamic_cast ---
    std::cout << "--- 4. dynamic_cast ---" << std::endl;

    // dynamic_cast проверяет тип во время выполнения:
    for (const auto& shape : shapes) {
        // Пытаемся привести к Circle:
        Circle* c = dynamic_cast<Circle*>(shape.get());
        if (c != nullptr) {
            std::cout << "  Найден круг! Радиус: " << c->get_radius() << std::endl;
        }
    }
    std::cout << std::endl;

    // --- 5. Множественное наследование ---
    std::cout << "--- 5. Множественное наследование ---" << std::endl;

    Document doc{"Заголовок", "Содержимое документа"};
    doc.print();                            // через Printable
    std::cout << "JSON: " << doc.serialize() << std::endl;  // через Serializable
    std::cout << std::endl;

    // --- Деструкторы будут вызваны автоматически ---
    std::cout << "--- Уничтожение объектов ---" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 10 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "ДОМАШНЕЕ ЗАДАНИЕ:" << std::endl;
    std::cout << "1. Добавьте класс Ellipse (эллипс)" << std::endl;
    std::cout << "2. Создайте иерархию Animal → Dog, Cat, Bird" << std::endl;
    std::cout << "3. Реализуйте паттерн 'Стратегия' через интерфейсы" << std::endl;
    std::cout << "4. Создайте класс Employee с наследниками Manager, Developer" << std::endl;
    std::cout << "5. Реализуйте полиморфную коллекцию транспортных средств" << std::endl;

    return 0;
}
