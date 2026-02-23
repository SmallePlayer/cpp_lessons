// =============================================================================
// Урок 16: Boost.Regex, Boost.JSON и сериализация
// =============================================================================
// Темы:
//   - Boost.Regex — регулярные выражения (vs std::regex)
//   - Boost.JSON — парсинг и создание JSON (Boost 1.75+)
//   - Boost.Serialization — сериализация объектов
//   - Boost.Program_options — аргументы командной строки
//   - Практические примеры
//
// УСТАНОВКА:
//   macOS:   brew install boost
//   Ubuntu:  sudo apt install libboost-all-dev
//   Windows: vcpkg install boost
//
// КОМПИЛЯЦИЯ:
//   g++ -std=c++17 lesson_16.cpp -lboost_regex -lboost_system
//   g++ -std=c++17 lesson_16.cpp -lboost_regex -lboost_json -lboost_system
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <regex>       // std::regex (аналог boost::regex)
#include <sstream>
#include <map>
#include <stdexcept>

// Boost заголовки (требуют установки Boost):
// #include <boost/regex.hpp>
// #include <boost/json.hpp>
// #include <boost/archive/text_oarchive.hpp>
// #include <boost/archive/text_iarchive.hpp>
// #include <boost/serialization/string.hpp>
// #include <boost/program_options.hpp>
// namespace bj = boost::json;
// namespace po = boost::program_options;

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 1: Boost.Regex vs std::regex
// ─────────────────────────────────────────────────────────────────────────────
//
// Boost.Regex — оригинальная библиотека регулярных выражений для C++.
// std::regex (C++11) — скопирована из Boost.Regex.
// API практически идентичен!
//
// Когда использовать Boost.Regex вместо std::regex:
//   - Нужна скорость: Boost.Regex работает быстрее std::regex
//   - Нужна поддержка Perl-синтаксиса
//   - Нужен Unicode (через Boost.Locale)
//
// Основные классы/функции:
//   boost::regex  r("паттерн")    — аналог std::regex
//   boost::regex_match(str, r)    — полное совпадение
//   boost::regex_search(str, r)   — поиск совпадения
//   boost::regex_replace(s, r, t) — замена
//   boost::smatch                 — аналог std::smatch (результат)
//
// ПРИМЕР С BOOST:
//   #include <boost/regex.hpp>
//
//   boost::regex email_re(R"([a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,})");
//   std::string email = "user@example.com";
//
//   if (boost::regex_match(email, email_re)) {
//       std::cout << "Валидный email!" << std::endl;
//   }
//
//   // Поиск всех совпадений:
//   std::string text = "Телефоны: 123-456, 789-012";
//   boost::regex phone_re(R"(\d{3}-\d{3})");
//   boost::sregex_iterator it(text.begin(), text.end(), phone_re);
//   boost::sregex_iterator end;
//   while (it != end) {
//       std::cout << it->str() << std::endl;
//       ++it;
//   }
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 2: Boost.JSON (Boost 1.75+)
// ─────────────────────────────────────────────────────────────────────────────
//
// Boost.JSON — современная, быстрая библиотека для работы с JSON.
//
// ПРИМЕР С BOOST:
//
//   #include <boost/json.hpp>
//   namespace bj = boost::json;
//
//   // Создание JSON:
//   bj::object obj;
//   obj["name"] = "Алексей";
//   obj["age"] = 25;
//   obj["scores"] = bj::array{95, 88, 92};
//   obj["active"] = true;
//
//   std::string json_str = bj::serialize(obj);
//   std::cout << json_str << std::endl;
//   // {"name":"Алексей","age":25,"scores":[95,88,92],"active":true}
//
//   // Парсинг JSON:
//   bj::value jv = bj::parse(json_str);
//   auto& parsed_obj = jv.as_object();
//   std::string name = bj::value_to<std::string>(parsed_obj["name"]);
//   int age = bj::value_to<int>(parsed_obj["age"]);
//   std::cout << name << ", " << age << " лет" << std::endl;
//
//   // Работа с массивами:
//   auto& arr = parsed_obj["scores"].as_array();
//   for (const auto& score : arr) {
//       std::cout << bj::value_to<int>(score) << " ";
//   }
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 3: Boost.Serialization
// ─────────────────────────────────────────────────────────────────────────────
//
// Boost.Serialization позволяет сериализовать C++ объекты.
//
// ПРИМЕР С BOOST:
//
//   #include <boost/archive/text_oarchive.hpp>
//   #include <boost/archive/text_iarchive.hpp>
//   #include <boost/serialization/string.hpp>
//   #include <boost/serialization/vector.hpp>
//
//   class Student {
//       std::string name;
//       int age;
//       std::vector<double> grades;
//
//       friend class boost::serialization::access;
//       template<class Archive>
//       void serialize(Archive& ar, const unsigned int version) {
//           ar & name;
//           ar & age;
//           ar & grades;
//       }
//
//   public:
//       Student() = default;
//       Student(std::string n, int a, std::vector<double> g)
//           : name(n), age(a), grades(g) {}
//
//       void print() const {
//           std::cout << name << ", " << age << " лет, оценки: ";
//           for (double g : grades) std::cout << g << " ";
//           std::cout << std::endl;
//       }
//   };
//
//   // Сериализация в строку:
//   Student s("Алексей", 20, {4.5, 5.0, 3.8});
//   std::ostringstream oss;
//   boost::archive::text_oarchive oa(oss);
//   oa << s;
//   std::string serialized = oss.str();
//
//   // Десериализация:
//   Student loaded;
//   std::istringstream iss(serialized);
//   boost::archive::text_iarchive ia(iss);
//   ia >> loaded;
//   loaded.print();
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 4: Boost.Program_options
// ─────────────────────────────────────────────────────────────────────────────
//
// Boost.Program_options — разбор аргументов командной строки.
//
// ПРИМЕР С BOOST:
//
//   #include <boost/program_options.hpp>
//   namespace po = boost::program_options;
//
//   po::options_description desc("Разрешённые опции");
//   desc.add_options()
//       ("help,h", "Показать помощь")
//       ("input,i", po::value<std::string>(), "Входной файл")
//       ("output,o", po::value<std::string>()->default_value("out.txt"), "Выходной файл")
//       ("verbose,v", "Подробный вывод")
//       ("count,n", po::value<int>()->default_value(1), "Количество итераций");
//
//   po::variables_map vm;
//   po::store(po::parse_command_line(argc, argv, desc), vm);
//   po::notify(vm);
//
//   if (vm.count("help")) {
//       std::cout << desc << std::endl;
//       return 0;
//   }
//
//   if (vm.count("input")) {
//       std::cout << "Входной файл: " << vm["input"].as<std::string>() << std::endl;
//   }
//
//   // Вызов: ./program -i input.txt -o output.txt --verbose -n 5
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// ДЕМОНСТРАЦИЯ (std::regex как аналог boost::regex)
// ─────────────────────────────────────────────────────────────────────────────

// Простой JSON-сериализатор (для демонстрации концепций Boost.JSON):
class SimpleJSON {
public:
    static std::string make_object(const std::map<std::string, std::string>& fields) {
        std::string result = "{";
        bool first = true;
        for (const auto& [key, value] : fields) {
            if (!first) result += ",";
            result += "\"" + key + "\":" + value;
            first = false;
        }
        result += "}";
        return result;
    }

    static std::string quote(const std::string& s) {
        return "\"" + s + "\"";
    }

    static std::string number(double n) {
        std::ostringstream oss;
        oss << n;
        return oss.str();
    }

    static std::string boolean(bool b) {
        return b ? "true" : "false";
    }

    static std::string make_array(const std::vector<std::string>& items) {
        std::string result = "[";
        for (size_t i = 0; i < items.size(); ++i) {
            if (i > 0) result += ",";
            result += items[i];
        }
        result += "]";
        return result;
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Урок 16: Boost.Regex, JSON, Сериализация" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =========================================================================
    // 1. std::regex как аналог boost::regex
    // =========================================================================
    std::cout << "--- 1. Регулярные выражения (std::regex ≈ boost::regex) ---" << std::endl;

    // Email валидация:
    std::regex email_re(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    std::vector<std::string> emails = {
        "user@example.com",
        "invalid-email",
        "admin@boost.org",
        "not_valid@",
        "test.user+tag@domain.co.uk"
    };

    std::cout << "Валидация email:" << std::endl;
    for (const auto& email : emails) {
        bool valid = std::regex_match(email, email_re);
        std::cout << "  " << email << ": " << (valid ? "валидный" : "невалидный") << std::endl;
    }
    std::cout << std::endl;

    // Поиск телефонов:
    std::cout << "Поиск телефонов в тексте:" << std::endl;
    std::string text = "Контакты: +7(123)456-78-90, 8-800-555-35-35, 495-123-4567";
    std::regex phone_re(R"(\+?[\d][\d\s\-\(\)]{6,})");

    auto phones_begin = std::sregex_iterator(text.begin(), text.end(), phone_re);
    auto phones_end = std::sregex_iterator();
    for (auto it = phones_begin; it != phones_end; ++it) {
        std::cout << "  Найден: " << it->str() << std::endl;
    }
    std::cout << std::endl;

    // Замена с regex_replace:
    std::string masked = std::regex_replace(
        text, phone_re, "[ТЕЛЕФОН]"
    );
    std::cout << "После маскировки: " << masked << std::endl;
    std::cout << std::endl;

    // Группы захвата:
    std::string date_str = "Дата: 2024-03-15";
    std::regex date_re(R"((\d{4})-(\d{2})-(\d{2}))");
    std::smatch match;

    if (std::regex_search(date_str, match, date_re)) {
        std::cout << "Найдена дата: " << match[0] << std::endl;
        std::cout << "  Год:   " << match[1] << std::endl;
        std::cout << "  Месяц: " << match[2] << std::endl;
        std::cout << "  День:  " << match[3] << std::endl;
    }
    std::cout << std::endl;

    // =========================================================================
    // 2. Простой JSON (аналог Boost.JSON)
    // =========================================================================
    std::cout << "--- 2. JSON сериализация (аналог Boost.JSON) ---" << std::endl;

    // Создание JSON объекта:
    std::map<std::string, std::string> person_fields;
    person_fields["name"] = SimpleJSON::quote("Алексей");
    person_fields["age"] = SimpleJSON::number(25);
    person_fields["active"] = SimpleJSON::boolean(true);
    person_fields["scores"] = SimpleJSON::make_array({
        SimpleJSON::number(95),
        SimpleJSON::number(88),
        SimpleJSON::number(92)
    });

    std::string json = SimpleJSON::make_object(person_fields);
    std::cout << "JSON объект:" << std::endl;
    std::cout << "  " << json << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 3. Простая сериализация (аналог Boost.Serialization)
    // =========================================================================
    std::cout << "--- 3. Сериализация (аналог Boost.Serialization) ---" << std::endl;

    struct Student {
        std::string name;
        int age;
        std::vector<double> grades;

        std::string serialize() const {
            std::ostringstream oss;
            oss << name << "|" << age << "|";
            for (size_t i = 0; i < grades.size(); ++i) {
                if (i > 0) oss << ",";
                oss << grades[i];
            }
            return oss.str();
        }

        static Student deserialize(const std::string& data) {
            Student s;
            std::istringstream iss(data);
            std::getline(iss, s.name, '|');
            std::string age_str;
            std::getline(iss, age_str, '|');
            s.age = std::stoi(age_str);
            std::string grades_str;
            std::getline(iss, grades_str);
            std::istringstream gs(grades_str);
            std::string g;
            while (std::getline(gs, g, ',')) {
                if (!g.empty()) s.grades.push_back(std::stod(g));
            }
            return s;
        }

        void print() const {
            std::cout << "  Студент: " << name << ", " << age << " лет, оценки: ";
            for (double g : grades) std::cout << g << " ";
            std::cout << std::endl;
        }
    };

    Student original{"Мария", 20, {4.5, 5.0, 3.8, 4.2}};
    std::cout << "Оригинал:" << std::endl;
    original.print();

    std::string serialized = original.serialize();
    std::cout << "Сериализовано: \"" << serialized << "\"" << std::endl;

    Student loaded = Student::deserialize(serialized);
    std::cout << "Десериализовано:" << std::endl;
    loaded.print();
    std::cout << std::endl;

    // =========================================================================
    // 4. Аналог Boost.Program_options
    // =========================================================================
    std::cout << "--- 4. Разбор аргументов (аналог Boost.Program_options) ---" << std::endl;

    // Простой парсер аргументов командной строки:
    struct ArgParser {
        std::map<std::string, std::string> args;

        void parse(int argc, char* argv[]) {
            for (int i = 1; i < argc; ++i) {
                std::string arg = argv[i];
                if (arg.substr(0, 2) == "--") {
                    std::string key = arg.substr(2);
                    if (i + 1 < argc && argv[i+1][0] != '-') {
                        args[key] = argv[++i];
                    } else {
                        args[key] = "true";
                    }
                }
            }
        }

        std::string get(const std::string& key,
                        const std::string& default_val = "") const {
            auto it = args.find(key);
            return (it != args.end()) ? it->second : default_val;
        }

        bool has(const std::string& key) const {
            return args.count(key) > 0;
        }
    };

    // Симуляция аргументов командной строки:
    const char* fake_argv[] = {"program", "--input", "data.txt",
                                "--output", "result.txt", "--verbose"};
    int fake_argc = 6;
    ArgParser parser;
    parser.parse(fake_argc, const_cast<char**>(fake_argv));

    std::cout << "Симуляция: program --input data.txt --output result.txt --verbose" << std::endl;
    std::cout << "  input:   " << parser.get("input", "(не указан)") << std::endl;
    std::cout << "  output:  " << parser.get("output", "out.txt") << std::endl;
    std::cout << "  verbose: " << (parser.has("verbose") ? "да" : "нет") << std::endl;
    std::cout << "  count:   " << parser.get("count", "1") << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 5. Установка Boost
    // =========================================================================
    std::cout << "--- 5. Установка и компиляция с Boost ---" << std::endl;
    std::cout << "macOS:   brew install boost" << std::endl;
    std::cout << "Ubuntu:  sudo apt install libboost-all-dev" << std::endl;
    std::cout << "Windows: vcpkg install boost" << std::endl;
    std::cout << std::endl;
    std::cout << "Компиляция с Boost.Regex:" << std::endl;
    std::cout << "  g++ -std=c++17 file.cpp -lboost_regex" << std::endl;
    std::cout << std::endl;
    std::cout << "Компиляция с Boost.JSON (Boost 1.75+):" << std::endl;
    std::cout << "  g++ -std=c++17 file.cpp -lboost_json" << std::endl;
    std::cout << std::endl;
    std::cout << "Компиляция с Boost.Serialization:" << std::endl;
    std::cout << "  g++ -std=c++17 file.cpp -lboost_serialization" << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 16 завершён!" << std::endl;
    std::cout << "  Курс по Boost завершён! Продолжайте изучение на boost.org" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "ДОМАШНЕЕ ЗАДАНИЕ:" << std::endl;
    std::cout << "1. Используйте regex для парсинга URL" << std::endl;
    std::cout << "2. Установите Boost и попробуйте boost::json" << std::endl;
    std::cout << "3. Реализуйте сериализацию класса с помощью Boost.Serialization" << std::endl;
    std::cout << "4. Напишите CLI программу с Boost.Program_options" << std::endl;
    std::cout << "5. Изучите Boost.Spirit для написания парсеров" << std::endl;

    return 0;
}
