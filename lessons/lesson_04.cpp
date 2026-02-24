// =============================================================================
//  4: Условия и логические операторы
// =============================================================================
// Темы:
//   - if, else if, else
//   - Операторы сравнения (==, !=, <, >, <=, >=)
//   - Логические операторы (&&, ||, !)
//   - switch/case
//   - Тернарный оператор (? :)
//   - Область видимости переменных в блоках
//   - Ранний return
//
// Аналогия с Python:
//   Python: if x > 0:          →  C++: if (x > 0) {
//   Python: elif x < 0:        →  C++: } else if (x < 0) {
//   Python: else:               →  C++: } else {
//   Python: and, or, not        →  C++: &&, ||, !
//   Python: match/case (3.10+)  →  C++: switch/case
// =============================================================================

#include <iostream>
#include <string>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   4: Условия и логика" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =====================================================================
    // 1. if / else if / else
    // =====================================================================
    // Синтаксис:
    //   if (условие) {
    //       // код, если условие истинно
    //   } else if (другое_условие) {
    //       // код, если первое ложно, а второе истинно
    //   } else {
    //       // код, если все условия ложны
    //   }
    //
    // : Условие должно быть в скобках ()!
    // : Тело — в фигурных скобках {}! (можно без, если одна строка,
    //         но это плохая практика — всегда пишите {})
    //
    // Python: отступы определяют блоки
    // C++:    {} определяют блоки (отступы — только для читаемости)

    std::cout << "--- 1. if / else if / else ---" << std::endl;

    int temperature{25};
    std::cout << "Температура: " << temperature << " градусов" << std::endl;

    if (temperature > 30) {
        std::cout << "Жарко!" << std::endl;
    } else if (temperature > 20) {
        std::cout << "Тепло и комфортно." << std::endl;
    } else if (temperature > 10) {
        std::cout << "Прохладно, возьмите куртку." << std::endl;
    } else if (temperature > 0) {
        std::cout << "Холодно!" << std::endl;
    } else {
        std::cout << "Мороз! Оставайтесь дома." << std::endl;
    }
    std::cout << std::endl;

    // =====================================================================
    // 2. ТЫ СЯ
    // =====================================================================
    //  ==  равно            (Python: ==)
    //  !=  не равно         (Python: !=)
    //  <   меньше           (Python: <)
    //  >   больше           (Python: >)
    //  <=  меньше или равно (Python: <=)
    //  >=  больше или равно (Python: >=)
    //
    // : == (сравнение) vs = (присваивание)!
    //   if (x = 5)  — это не сравнение! Это присваивание!
    //   if (x == 5) — вот это сравнение!
    //   Частая ошибка новичков! Компилятор может предупредить.

    std::cout << "--- 2. Операторы сравнения ---" << std::endl;

    int a{10}, b{20};
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a == b: " << std::boolalpha << (a == b) << std::endl;
    std::cout << "a != b: " << std::boolalpha << (a != b) << std::endl;
    std::cout << "a < b:  " << std::boolalpha << (a < b) << std::endl;
    std::cout << "a > b:  " << std::boolalpha << (a > b) << std::endl;
    std::cout << "a <= b: " << std::boolalpha << (a <= b) << std::endl;
    std::cout << "a >= b: " << std::boolalpha << (a >= b) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 3. С ТЫ
    // =====================================================================
    //  &&  логическое И   (Python: and)
    //  ||  логическое ИЛИ  (Python: or)
    //  !   логическое НЕ  (Python: not)
    //
    // Короткое замыкание (short-circuit evaluation):
    //   false && ... — второе выражение не вычисляется
    //   true  || ... — второе выражение не вычисляется
    //   (Точно так же, как в Python!)

    std::cout << "--- 3. Логические операторы ---" << std::endl;

    int age{25};
    bool has_license{true};
    bool is_insured{false};

    std::cout << "Возраст: " << age << std::endl;
    std::cout << "Есть права: " << std::boolalpha << has_license << std::endl;
    std::cout << "Есть страховка: " << std::boolalpha << is_insured << std::endl;

    if (age >= 18 && has_license) {
        std::cout << "Можно водить машину!" << std::endl;
    }

    if (has_license || is_insured) {
        std::cout << "Хотя бы одно условие выполнено." << std::endl;
    }

    if (!is_insured) {
        std::cout << "Нужно оформить страховку!" << std::endl;
    }
    std::cout << std::endl;

    // =====================================================================
    // 4. Ы СЯ
    // =====================================================================
    std::cout << "--- 4. Вложенные условия ---" << std::endl;

    int score{85};
    std::cout << "Оценка: " << score << std::endl;

    // Система оценок:
    char grade;
    if (score >= 90) {
        grade = 'A';
    } else if (score >= 80) {
        grade = 'B';
    } else if (score >= 70) {
        grade = 'C';
    } else if (score >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }
    std::cout << "Оценка: " << grade << std::endl;

    // С вложением:
    if (grade == 'A' || grade == 'B') {
        std::cout << "Отличный результат!" << std::endl;
        if (score == 100) {
            std::cout << "Идеально! Максимальный балл!" << std::endl;
        }
    } else if (grade == 'F') {
        std::cout << "Нужно пересдать!" << std::endl;
    }
    std::cout << std::endl;

    // =====================================================================
    // 5. switch / case
    // =====================================================================
    // switch проверяет переменную на соответствие конкретным значениям.
    // Работает только с целыми числами, char и enum!
    // (не работает со строками и float/double!)
    //
    // : Не забывайте break! ез него выполнение «провалится»
    // (fall-through) в следующий case!
    //
    // Python аналогия: match/case (Python 3.10+)
    //   match value:
    //       case 1: ...
    //       case 2: ...
    //
    // C++:
    //   switch (value) {
    //       case 1: ...; break;
    //       case 2: ...; break;
    //       default: ...;
    //   }

    std::cout << "--- 5. switch / case ---" << std::endl;

    int day{3};
    std::cout << "День недели (число): " << day << std::endl;

    switch (day) {
        case 1:
            std::cout << "Понедельник" << std::endl;
            break;
        case 2:
            std::cout << "Вторник" << std::endl;
            break;
        case 3:
            std::cout << "Среда" << std::endl;
            break;
        case 4:
            std::cout << "Четверг" << std::endl;
            break;
        case 5:
            std::cout << "Пятница" << std::endl;
            break;
        case 6:
        case 7:
            std::cout << "Выходной!" << std::endl;
            break;
        default:
            std::cout << "Некорректный день!" << std::endl;
            break;
    }
    std::cout << std::endl;

    // switch с char:
    char operation{'+'};
    int x{10}, y{3};
    std::cout << x << " " << operation << " " << y << " = ";

    switch (operation) {
        case '+': std::cout << (x + y) << std::endl; break;
        case '-': std::cout << (x - y) << std::endl; break;
        case '*': std::cout << (x * y) << std::endl; break;
        case '/': std::cout << (x / y) << std::endl; break;
        default:  std::cout << "?" << std::endl; break;
    }
    std::cout << std::endl;

    // =====================================================================
    // 6. ТЫ Т (? :)
    // =====================================================================
    // Краткая форма if/else для получения значения.
    //
    // Синтаксис: условие ? значение_если_true : значение_если_false
    //
    // Python: result = "да" if condition else "нет"
    // C++:    result = condition ? "да" : "нет";
    //
    // Используйте для простых условий. ля сложных — обычный if.

    std::cout << "--- 6. Тернарный оператор ---" << std::endl;

    int num{42};
    std::string parity = (num % 2 == 0) ? "чётное" : "нечётное";
    std::cout << num << " — " << parity << " число" << std::endl;

    int abs_val{-15};
    int absolute = (abs_val >= 0) ? abs_val : -abs_val;
    std::cout << "abs(" << abs_val << ") = " << absolute << std::endl;

    // ложенный тернарный ( рекомендуется — плохо читается!):
    int val{75};
    std::string level = (val >= 90) ? "отлично"
                      : (val >= 70) ? "хорошо"
                      : (val >= 50) ? "удовлетворительно"
                      : "неудовлетворительно";
    std::cout << "Оценка " << val << ": " << level << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 7. СТЬ СТ  Х
    // =====================================================================
    // Переменная, объявленная внутри {}, видна только внутри этих {}.
    //
    // Python: переменные из if-блока видны и после него!
    //   if True:
    //       x = 10
    //   print(x)  # Работает! x = 10
    //
    // C++: переменные из if-блока не видны снаружи!
    //   if (true) {
    //       int x = 10;
    //   }
    //   std::cout << x;  // Ш! x не существует здесь!

    std::cout << "--- 7. Область видимости ---" << std::endl;

    int outer{100};
    std::cout << "outer = " << outer << std::endl;

    if (true) {
        int inner{200};  // Видна только здесь!
        std::cout << "inner (внутри if) = " << inner << std::endl;
        std::cout << "outer (внутри if) = " << outer << std::endl;
    }
    // std::cout << inner;  // Ш! inner не существует здесь!
    std::cout << "outer (после if) = " << outer << " (доступна)" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 8. ЪЯ   if (C++17)
    // =====================================================================
    // if (init; condition) — можно объявить переменную прямо в if!
    // Переменная видна только внутри if/else.
    //
    // Python аналогия (3.8+): if (n := len(list)) > 0:
    // C++ (C++17): if (int n = getValue(); n > 0) { ... }

    std::cout << "--- 8. Переменная в if (C++17) ---" << std::endl;

    // C++17: init-statement в if
    if (int result = 42 * 2; result > 50) {
        std::cout << "result = " << result << " (больше 50)" << std::endl;
    } else {
        std::cout << "result = " << result << " (50 или меньше)" << std::endl;
    }
    // result здесь уже не доступен
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 4 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. Напишите калькулятор с switch для операций +,-,*,/" << std::endl;
    std::cout << "2. Определите, является ли год високосным" << std::endl;
    std::cout << "3. Определите тип треугольника по длинам сторон" << std::endl;
    std::cout << "4. Конвертируйте числовую оценку (0-100) в буквенную" << std::endl;
    std::cout << "5. Решите квадратное уравнение (ax^2 + bx + c = 0)" << std::endl;

    return 0;
}