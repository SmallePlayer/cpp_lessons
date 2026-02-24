// =============================================================================
//  7: Массивы, Векторы и Контейнеры STL
// =============================================================================
// Темы:
//   - C-массивы (статические)
//   - std::array (C++11) — безопасная обёртка
//   - std::vector — динамический массив (аналог Python list)
//   - Основные методы vector
//   - std::map и std::unordered_map (аналог Python dict)
//   - std::set и std::unordered_set (аналог Python set)
//   - Итераторы — основы
//   - Алгоритмы STL (sort, find, count, etc.)
//
// Аналогия с Python:
//   Python: list         →  C++: std::vector
//   Python: dict         →  C++: std::map / std::unordered_map
//   Python: set          →  C++: std::set / std::unordered_set
//   Python: tuple        →  C++: std::tuple / std::pair
// =============================================================================

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>    // sort, find, count, etc.
#include <numeric>      // accumulate, iota
#include <string>
#include <tuple>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   7: Контейнеры STL" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =====================================================================
    // 1. C-ССЫ (СТТС)
    // =====================================================================
    // int arr[5] = {1, 2, 3, 4, 5};
    //
    // Проблемы C-массивов:
    // - Фиксированный размер (нельзя изменить)
    // - Нет проверки границ (выход за массив = UB!)
    // - Не знают свой размер при передаче в функцию
    // - Нет методов (length, push_back, etc.)
    //
    // : не используйте C-массивы! Используйте std::array или std::vector!

    std::cout << "--- 1. C-массивы (не рекомендуется) ---" << std::endl;

    int c_arr[5] = {10, 20, 30, 40, 50};
    std::cout << "c_arr[0] = " << c_arr[0] << std::endl;
    std::cout << "c_arr[4] = " << c_arr[4] << std::endl;
    // c_arr[10] = 999;  // UB! Компилятор не предупредит!

    // Размер C-массива:
    std::cout << "sizeof(c_arr) = " << sizeof(c_arr) << " байт" << std::endl;
    std::cout << "Количество элементов: " << (sizeof(c_arr) / sizeof(c_arr[0])) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 2. std::array (C++11) — СЫ СС С 
    // =====================================================================
    // std::array<тип, размер> name = {значения};
    //
    // Преимущества перед C-массивом:
    // - Знает свой размер: arr.size()
    // - Проверка границ: arr.at(i) бросает исключение
    // - Работает с алгоритмами STL
    // - Можно копировать и сравнивать
    //
    // Python: tuple (неизменяемая последовательность)

    std::cout << "--- 2. std::array ---" << std::endl;

    std::array<int, 5> arr = {10, 20, 30, 40, 50};
    std::cout << "arr.size() = " << arr.size() << std::endl;
    std::cout << "arr[0] = " << arr[0] << std::endl;
    std::cout << "arr.at(2) = " << arr.at(2) << " (с проверкой границ)" << std::endl;
    std::cout << "arr.front() = " << arr.front() << std::endl;
    std::cout << "arr.back() = " << arr.back() << std::endl;

    // Range-based for:
    std::cout << "Элементы: ";
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 3. std::vector — С СС
    // =====================================================================
    // std::vector — главный контейнер в C++!
    // то аналог Python list, но типизированный.
    //
    // Может расти и уменьшаться.
    // Хранит элементы в непрерывной памяти (как массив).
    //
    // Python: my_list = [1, 2, 3]        →  C++: std::vector<int> vec = {1, 2, 3};
    // Python: my_list.append(4)           →  C++: vec.push_back(4);
    // Python: len(my_list)                →  C++: vec.size();
    // Python: my_list[0]                  →  C++: vec[0] или vec.at(0)
    // Python: my_list.pop()               →  C++: vec.pop_back();
    // Python: my_list.insert(1, 99)       →  C++: vec.insert(vec.begin()+1, 99);

    std::cout << "--- 3. std::vector ---" << std::endl;

    // Создание:
    std::vector<int> v1;                     // устой
    std::vector<int> v2{1, 2, 3, 4, 5};     // С элементами
    std::vector<int> v3(5, 0);               // 5 нулей: {0, 0, 0, 0, 0}
    std::vector<std::string> words{"hello", "world", "cpp"};

    // Добавление элементов:
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);

    std::cout << "v1 после push_back: ";
    for (const auto& elem : v1) std::cout << elem << " ";
    std::cout << std::endl;

    // Размер и ёмкость:
    std::cout << "v2.size() = " << v2.size() << std::endl;
    std::cout << "v2.capacity() = " << v2.capacity() << " (выделенная память)" << std::endl;
    std::cout << "v2.empty() = " << std::boolalpha << v2.empty() << std::endl;

    // Доступ:
    std::cout << "v2[0] = " << v2[0] << std::endl;
    std::cout << "v2.at(2) = " << v2.at(2) << std::endl;
    std::cout << "v2.front() = " << v2.front() << std::endl;
    std::cout << "v2.back() = " << v2.back() << std::endl;

    // Удаление:
    v2.pop_back();  // Удаляет последний элемент
    std::cout << "После pop_back: ";
    for (const auto& elem : v2) std::cout << elem << " ";
    std::cout << std::endl;

    // Вставка в середину:
    v2.insert(v2.begin() + 1, 99);
    std::cout << "После insert(1, 99): ";
    for (const auto& elem : v2) std::cout << elem << " ";
    std::cout << std::endl;

    // Очистка:
    // v2.clear();  // Удаляет все элементы
    std::cout << std::endl;

    // =====================================================================
    // 4. ТЫ STL Я Т
    // =====================================================================
    // <algorithm> — заголовочный файл с десятками полезных алгоритмов!
    //
    // Python: sorted(list)          →  C++: std::sort(v.begin(), v.end())
    // Python: list.reverse()        →  C++: std::reverse(v.begin(), v.end())
    // Python: x in list             →  C++: std::find(v.begin(), v.end(), x)
    // Python: list.count(x)         →  C++: std::count(v.begin(), v.end(), x)
    // Python: min(list), max(list)  →  C++: *std::min_element(...), *std::max_element(...)
    // Python: sum(list)             →  C++: std::accumulate(v.begin(), v.end(), 0)

    std::cout << "--- 4. Алгоритмы STL ---" << std::endl;

    std::vector<int> nums{5, 2, 8, 1, 9, 3, 7, 4, 6};

    std::cout << "Исходный: ";
    for (const auto& n : nums) std::cout << n << " ";
    std::cout << std::endl;

    // Сортировка:
    std::sort(nums.begin(), nums.end());
    std::cout << "sort():   ";
    for (const auto& n : nums) std::cout << n << " ";
    std::cout << std::endl;

    // Обратная сортировка:
    std::sort(nums.begin(), nums.end(), std::greater<int>());
    std::cout << "sort(>):  ";
    for (const auto& n : nums) std::cout << n << " ";
    std::cout << std::endl;

    // Реверс:
    std::reverse(nums.begin(), nums.end());
    std::cout << "reverse():";
    for (const auto& n : nums) std::cout << n << " ";
    std::cout << std::endl;

    // Поиск:
    auto it = std::find(nums.begin(), nums.end(), 5);
    if (it != nums.end()) {
        std::cout << "find(5): найдено на позиции " << (it - nums.begin()) << std::endl;
    }

    // Подсчёт:
    std::vector<int> data{1, 2, 3, 2, 1, 2, 3, 2};
    std::cout << "count(2) в {1,2,3,2,1,2,3,2} = " << std::count(data.begin(), data.end(), 2) << std::endl;

    // Мин/Макс:
    auto min_it = std::min_element(nums.begin(), nums.end());
    auto max_it = std::max_element(nums.begin(), nums.end());
    std::cout << "min = " << *min_it << ", max = " << *max_it << std::endl;

    // Сумма:
    int total = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "sum = " << total << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 5. std::map — ССТЫ СС (СЬ)
    // =====================================================================
    // std::map<ключ, значение> — упорядоченный (по ключу) словарь
    // Реализован как красно-чёрное дерево.
    // Доступ/вставка/удаление: O(log n)
    //
    // std::unordered_map — неупорядоченный (хеш-таблица)
    // оступ/вставка/удаление: O(1) в среднем
    //
    // Python: dict (аналог unordered_map)
    //   Python: d = {"key": "value"}
    //   Python: d["key"] → "value"
    //   Python: "key" in d → True

    std::cout << "--- 5. std::map ---" << std::endl;

    std::map<std::string, int> ages;
    ages["Алексей"] = 25;
    ages["Мария"] = 30;
    ages["Иван"] = 22;
    ages.insert({"Елена", 28});

    // Перебор (упорядочен по ключу!):
    for (const auto& [name, age] : ages) {  // Structured bindings (C++17)
        std::cout << "  " << name << ": " << age << " лет" << std::endl;
    }

    // Поиск:
    if (ages.count("Алексей") > 0) {
        std::cout << "Алексей найден, возраст: " << ages["Алексей"] << std::endl;
    }

    // find() — более безопасный способ:
    auto search = ages.find("Мария");
    if (search != ages.end()) {
        std::cout << "Мария найдена: " << search->second << " лет" << std::endl;
    }

    std::cout << "Размер map: " << ages.size() << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 6. std::unordered_map — ЫСТЫ СЬ
    // =====================================================================
    std::cout << "--- 6. std::unordered_map ---" << std::endl;

    std::unordered_map<std::string, double> prices;
    prices["яблоко"] = 1.50;
    prices["банан"] = 0.75;
    prices["вишня"] = 3.00;

    for (const auto& [item, price] : prices) {
        std::cout << "  " << item << ": " << price << " руб" << std::endl;
    }
    std::cout << "(порядок может быть любым — это хеш-таблица!)" << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 7. std::set — СТ
    // =====================================================================
    // std::set<тип> — упорядоченное множество уникальных элементов
    // std::unordered_set — неупорядоченное множество
    //
    // Python: my_set = {1, 2, 3}  →  C++: std::set<int> s = {1, 2, 3};
    // Python: my_set.add(4)       →  C++: s.insert(4);
    // Python: 2 in my_set         →  C++: s.count(2) > 0  или  s.contains(2) (C++20)

    std::cout << "--- 7. std::set ---" << std::endl;

    std::set<int> unique_nums{5, 3, 1, 4, 1, 5, 3};  // Дубликаты удалятся!
    std::cout << "set{5,3,1,4,1,5,3}: ";
    for (const auto& n : unique_nums) {
        std::cout << n << " ";  // 1 3 4 5 (отсортировано, без дубликатов!)
    }
    std::cout << std::endl;

    unique_nums.insert(2);
    unique_nums.insert(1);  // Дубликат — не добавится
    std::cout << "После insert(2, 1): ";
    for (const auto& n : unique_nums) std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "count(3) = " << unique_nums.count(3) << std::endl;
    std::cout << "count(99) = " << unique_nums.count(99) << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 8. std::pair  std::tuple
    // =====================================================================
    // std::pair<тип1, тип2> — пара значений
    // std::tuple<типы...> — кортеж (несколько значений)
    //
    // Python: (x, y)         →  C++: std::pair<int,int>{x, y}
    // Python: (x, y, z)      →  C++: std::tuple<int,int,int>{x, y, z}
    // Python: a, b = pair     →  C++: auto [a, b] = pair;  (C++17)

    std::cout << "--- 8. pair и tuple ---" << std::endl;

    std::pair<std::string, int> person{"Алексей", 25};
    std::cout << "pair: " << person.first << ", " << person.second << std::endl;

    // Structured bindings (C++17):
    auto [name2, age2] = person;
    std::cout << "Деструктуризация: name=" << name2 << ", age=" << age2 << std::endl;

    // tuple:
    std::tuple<std::string, int, double> record{"Мария", 30, 4.5};
    auto [r_name, r_age, r_gpa] = record;
    std::cout << "tuple: " << r_name << ", " << r_age << ", GPA: " << r_gpa << std::endl;
    std::cout << std::endl;

    // =====================================================================
    // 9. 2D Т (Т)
    // =====================================================================
    // Python: matrix = [[1,2,3], [4,5,6], [7,8,9]]
    // C++: vector<vector<int>> matrix = {{1,2,3}, {4,5,6}, {7,8,9}};

    std::cout << "--- 9. 2D вектор ---" << std::endl;

    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::cout << "Матрица 3x3:" << std::endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 7 завершён!" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Я Я Т:" << std::endl;
    std::cout << "1. Реализуйте подсчёт слов в тексте (map)" << std::endl;
    std::cout << "2. Удалите дубликаты из вектора с помощью set" << std::endl;
    std::cout << "3. Отсортируйте вектор строк по длине (лямбда)" << std::endl;
    std::cout << "4. Реализуйте транспонирование матрицы" << std::endl;
    std::cout << "5. Создайте телефонную книгу на map" << std::endl;

    return 0;
}