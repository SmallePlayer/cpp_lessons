// =============================================================================
//  4: словия и логические операторы
// =============================================================================
// Темы:
//   - if, else if, else
//   - ператоры сравнения (==, !=, <, >, <=, >=)
//   - огические операторы (&&, ||, !)
//   - switch/case
//   - Тернарный оператор (? :)
//   - бласть видимости переменных в блоках
//   - анний return
//
// налогия с Python:
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
    std::cout << "   4: словия и логика" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =====================================================================
    // 1. if / else if / else
    // =====================================================================
    // Синтаксис:
    //   if (условие) {
    //       // код, если условие СТ
    //   } else if (другое_условие) {
    //       // код, если  ложно, а Т истинно
    //   } else {
    //       // код, если С условия ложны
    //   }
    //
    // : словие ЯТЬ в скобках ()!
    // : Тело — в фигурных скобках {}! (можно без, если одна строка,
    //         но это ХЯ Т — всегда пишите {})
    //
    // Python: отступы определяют блоки
    // C++:    {} определяют блоки (отступы — только для читаемости)

    std::cout << "--- 1. if / else if / else ---" << std::endl;

    int temperature{25};
    std::cout << "Температура: " << temperature << " градусов" << std::endl;

    if (temperature > 30) {
        std::cout << "арко!" << std::endl;
    } else if (temperature > 20) {
        std::cout << "Тепло и комфортно." << std::endl;
    } else if (temperature > 10) {
        std::cout << "рохладно, возьмите куртку." << std::endl;
    } else if (temperature > 0) {
        std::cout << "Холодно!" << std::endl;
    } else {
        std::cout << "ороз! ставайтесь дома." << std::endl;
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
    //   if (x = 5)  — это  сравнение! то присваивание!
    //   if (x == 5) — Т Т сравнение!
    //   астая ошибка новичков! омпилятор может предупредить.

    std::cout << "--- 2. ператоры сравнения ---" << std::endl;

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
    //  &&  логическое   (Python: and)
    //  ||  логическое  (Python: or)
    //  !   логическое  (Python: not)
    //
    // ороткое замыкание (short-circuit evaluation):
    //   false && ... — второе выражение  вычисляется
    //   true  || ... — второе выражение  вычисляется
    //   (Точно так же, как в Python!)

    std::cout << "--- 3. огические операторы ---" << std::endl;

    int age{25};
    bool has_license{true};
    bool is_insured{false};

    std::cout << "озраст: " << age << std::endl;
    std::cout << "сть права: " << std::boolalpha << has_license << std::endl;
    std::cout << "сть страховка: " << std::boolalpha << is_insured << std::endl;

    if (age >= 18 && has_license) {
        std::cout << "ожно водить машину!" << std::endl;
    }

    if (has_license || is_insured) {
        std::cout << "Хотя бы одно условие выполнено." << std::endl;
    }

    if (!is_insured) {
        std::cout << "ужно оформить страховку!" << std::endl;
    }
    std::cout << std::endl;

    // =====================================================================
    // 4. Ы СЯ
    // =====================================================================
    std::cout << "--- 4. ложенные условия ---" << std::endl;

    int score{85};
    std::cout << "ценка: " << score << std::endl;

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
    std::cout << "ценка: " << grade << std::endl;

    // С вложением:
    if (grade == 'A' || grade == 'B') {
        std::cout << "тличный результат!" << std::endl;
        if (score == 100) {
            std::cout << "деально! аксимальный балл!" << std::endl;
        }
    } else if (grade == 'F') {
        std::cout << "ужно пересдать!" << std::endl;
    }
    std::cout << std::endl;

    // =====================================================================
    // 5. switch / case
    // =====================================================================
    // switch проверяет переменную на соответствие ТЫ значениям.
    // аботает ТЬ с целыми числами, char и enum!
    // ( работает со строками и float/double!)
    //
    // : е забывайте break! ез него выполнение «провалится»
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
    std::cout << "ень недели (число): " << day << std::endl;

    switch (day) {
        case 1:
            std::cout << "онедельник" << std::endl;
            break;
        case 2:
            std::cout << "торник" << std::endl;
            break;
        case 3:
            std::cout << "Среда" << std::endl;
            break;
        case 4:
            std::cout << "етверг" << std::endl;
            break;
        case 5:
            std::cout << "ятница" << std::endl;
            break;
        case 6:
        case 7:
            std::cout << "ыходной!" << std::endl;
            break;
        default:
            std::cout << "екорректный день!" << std::endl;
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
    // раткая форма if/else для  значения.
    //
    // Синтаксис: условие ? значение_если_true : значение_если_false
    //
    // Python: result = "да" if condition else "нет"
    // C++:    result = condition ? "да" : "нет";
    //
    // спользуйте для СТЫХ условий. ля сложных — обычный if.

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
    std::cout << "ценка " << val << ": " << level << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 7. СТЬ СТ  Х
    // =====================================================================
    // еременная, объявленная внутри {}, видна ТЬ внутри этих {}.
    //
    // Python: переменные из if-блока видны и после него!
    //   if True:
    //       x = 10
    //   print(x)  # аботает! x = 10
    //
    // C++: переменные из if-блока  видны снаружи!
    //   if (true) {
    //       int x = 10;
    //   }
    //   std::cout << x;  // Ш! x не существует здесь!

    std::cout << "--- 7. бласть видимости ---" << std::endl;

    int outer{100};
    std::cout << "outer = " << outer << std::endl;

    if (true) {
        int inner{200};  // идна только здесь!
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
    // еременная видна только внутри if/else.
    //
    // Python аналогия (3.8+): if (n := len(list)) > 0:
    // C++ (C++17): if (int n = getValue(); n > 0) { ... }

    std::cout << "--- 8. еременная в if (C++17) ---" << std::endl;

    // C++17: init-statement в if
    if (int result = 42 * 2; result > 50) {
        std::cout << "result = " << result << " (больше 50)" << std::endl;
    } else {
        std::cout << "result = " << result << " (50 или меньше)" << std::endl;
    }
    // result здесь уже не доступен
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  рок 4 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. апишите калькулятор с switch для операций +,-,*,/" << std::endl;
    std::cout << "2. пределите, является ли год високосным" << std::endl;
    std::cout << "3. пределите тип треугольника по длинам сторон" << std::endl;
    std::cout << "4. онвертируйте числовую оценку (0-100) в буквенную" << std::endl;
    std::cout << "5. ешите квадратное уравнение (ax^2 + bx + c = 0)" << std::endl;

    return 0;
}