// =============================================================================
//  10: аследование и олиморфизм ( — асть 2)
// =============================================================================
// Темы:
//   - аследование (inheritance)
//   - одификаторы доступа при наследовании
//   - иртуальные функции (virtual)
//   - олиморфизм — ключевая концепция 
//   - override и final (C++11)
//   - бстрактные классы (чисто виртуальные функции)
//   - ножественное наследование
//   - dynamic_cast
//
// налогия с Python:
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
// ТЯ: аследование
// ─────────────────────────────────────────────────────────────────────────────
// аследование позволяет создавать новые классы на основе существующих.
//
// азовый класс (base/parent)  — от которого наследуют
// роизводный класс (derived/child) — который наследует
//
// class Derived : public Base {
//     // Derived имеет С члены Base + свои собственные
// };
//
// одификаторы наследования:
//   public    — public остаётся public, protected остаётся protected
//   protected — public → protected, protected → protected
//   private   — всё становится private
//
// С используйте public наследование!
// ─────────────────────────────────────────────────────────────────────────────

// =====================================================================
// 1. Ы СС: Shape (игура)
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
        // иртуальный деструктор — ЯТ для базовых классов!
        // ез него delete для указателя на базовый класс  вызовет
        // деструктор наследника → утечка ресурсов!
        std::cout << "  [~Shape] далена фигура: " << name << std::endl;
    }

    // ─── ТЬЫ  ───
    // virtual — функция может быть  в наследнике.
    // ызывается правильная версия в зависимости от Ь типа объекта.
    //
    //  virtual: вызывается версия по типу ТЯ (статическая привязка)
    // С virtual:   вызывается версия по типу ЪТ (динамическая привязка)
    //
    // Python: С методы виртуальные по умолчанию!
    // C++:    ужно Я указать virtual!

    virtual double area() const = 0;          // = 0 → СТ виртуальная (абстрактная)
    virtual double perimeter() const = 0;     // аследники ЯЫ реализовать!

    virtual void describe() const {
        std::cout << "  игура: " << name << ", цвет: " << color << std::endl;
    }

    const std::string& get_name() const { return name; }
};

// =====================================================================
// 2. С: Circle (руг)
// =====================================================================

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r, const std::string& c = "красный")
        : Shape("руг", c), radius(r) {}

    // override (C++11) — явно указывает, что мы переопределяем виртуальную функцию.
    // сли в базовом классе нет такой виртуальной функции — Ш компиляции!
    // то защита от опечаток.
    double area() const override {
        return 3.14159265358979323846 * radius * radius;
    }

    double perimeter() const override {
        return 2.0 * 3.14159265358979323846 * radius;
    }

    void describe() const override {
        Shape::describe();  // ызов метода  класса
        std::cout << "  адиус: " << radius << ", лощадь: " << area() << std::endl;
    }

    double get_radius() const { return radius; }
};

// =====================================================================
// 3. С: Rectangle (рямоугольник)
// =====================================================================

class Rectangle : public Shape {
protected:
    double width, height;

public:
    Rectangle(double w, double h, const std::string& c = "синий")
        : Shape("рямоугольник", c), width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2.0 * (width + height);
    }

    void describe() const override {
        Shape::describe();
        std::cout << "  " << width << " x " << height
                  << ", лощадь: " << area() << std::endl;
    }
};

// =====================================================================
// 4. С Т С: Square (вадрат от рямоугольника)
// =====================================================================

class Square : public Rectangle {
public:
    // final (C++11) — запрещает дальнейшее наследование или переопределение
    Square(double side, const std::string& c = "зелёный")
        : Rectangle(side, side, c) {
        name = "вадрат";  // зменяем protected поле базового класса
    }

    void describe() const override final {  // final — нельзя переопределить далее
        Shape::describe();
        std::cout << "  Сторона: " << width << ", лощадь: " << area() << std::endl;
    }
};

// =====================================================================
// 5. С: Triangle (Треугольник)
// =====================================================================

class Triangle : public Shape {
private:
    double a, b, c_side;

public:
    Triangle(double a, double b, double c, const std::string& col = "жёлтый")
        : Shape("Треугольник", col), a(a), b(b), c_side(c) {}

    double area() const override {
        // ормула ерона:
        double s = (a + b + c_side) / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c_side));
    }

    double perimeter() const override {
        return a + b + c_side;
    }
};

// =====================================================================
// 6. ТС (чисто абстрактный класс)
// =====================================================================
// ласс, где С методы = 0 (чисто виртуальные).
// ельзя создать экземпляр!
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

// ножественное наследование: наследуем от двух интерфейсов
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
    std::cout << "   10: аследование и олиморфизм" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // --- 1. Создание объектов ---
    std::cout << "--- 1. Создание фигур ---" << std::endl;

    Circle circle{5.0};
    Rectangle rect{4.0, 6.0};
    Square square{3.0};
    Triangle tri{3.0, 4.0, 5.0};
    std::cout << std::endl;

    // --- 2. ызов методов ---
    std::cout << "--- 2. етоды объектов ---" << std::endl;
    circle.describe();
    std::cout << std::endl;
    rect.describe();
    std::cout << std::endl;
    square.describe();
    std::cout << std::endl;

    // --- 3.  — главная сила ! ---
    std::cout << "--- 3. олиморфизм ---" << std::endl;

    // ектор указателей на Ы класс, но содержит Ы объекты!
    // ызывается ЬЫ метод для каждого объекта!
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Square>(3.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));

    std::cout << "\nсе фигуры (полиморфный вызов):" << std::endl;
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
        // ытаемся привести к Circle:
        Circle* c = dynamic_cast<Circle*>(shape.get());
        if (c != nullptr) {
            std::cout << "  айден круг! адиус: " << c->get_radius() << std::endl;
        }
    }
    std::cout << std::endl;

    // --- 5. ножественное наследование ---
    std::cout << "--- 5. ножественное наследование ---" << std::endl;

    Document doc{"аголовок", "Содержимое документа"};
    doc.print();                            // через Printable
    std::cout << "JSON: " << doc.serialize() << std::endl;  // через Serializable
    std::cout << std::endl;

    // --- еструкторы будут вызваны автоматически ---
    std::cout << "--- ничтожение объектов ---" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  рок 10 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. обавьте класс Ellipse (эллипс)" << std::endl;
    std::cout << "2. Создайте иерархию Animal → Dog, Cat, Bird" << std::endl;
    std::cout << "3. еализуйте паттерн 'Стратегия' через интерфейсы" << std::endl;
    std::cout << "4. Создайте класс Employee с наследниками Manager, Developer" << std::endl;
    std::cout << "5. еализуйте полиморфную коллекцию транспортных средств" << std::endl;

    return 0;
}