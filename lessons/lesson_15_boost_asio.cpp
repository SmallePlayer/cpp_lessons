// =============================================================================
// Урок 15: Boost.Asio — Асинхронный ввод-вывод и работа с сетью
// =============================================================================
// Boost.Asio — одна из самых важных библиотек Boost.
// Она обеспечивает асинхронный ввод-вывод для:
//   - Сетевого программирования (TCP/UDP сокеты)
//   - Таймеров
//   - Последовательных портов
//   - Файловых потоков (на некоторых платформах)
//
// Темы:
//   - io_context — «движок» асинхронных операций
//   - Синхронный TCP-клиент и сервер
//   - Асинхронный сервер
//   - Таймеры (steady_timer)
//   - Корутины с Asio (C++20)
//   - Strand — синхронизация в многопоточности
//
// УСТАНОВКА:
//   macOS:   brew install boost
//   Ubuntu:  sudo apt install libboost-all-dev
//   Windows: vcpkg install boost
//
// КОМПИЛЯЦИЯ (требует Boost.Asio):
//   g++     -std=c++17 lesson_15.cpp -lboost_system -pthread
//   clang++ -std=c++17 lesson_15.cpp -lboost_system -pthread
//
//   Или header-only (без линковки с -lboost_system):
//   g++ -std=c++17 -DBOOST_ASIO_STANDALONE lesson_15.cpp -pthread
//
// С C++20 Asio вошёл в обсуждение как часть стандарта (Networking TS).
// Также существует самостоятельная версия: https://think-async.com/Asio/
// =============================================================================

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <atomic>
#include <mutex>

// Boost.Asio заголовки (требуют установки Boost):
// #include <boost/asio.hpp>
// #include <boost/asio/steady_timer.hpp>
// namespace asio = boost::asio;
// using asio::ip::tcp;

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 1: Что такое Boost.Asio?
// ─────────────────────────────────────────────────────────────────────────────
//
// Asio реализует модель "реактор" (Reactor Pattern) для I/O:
//
//   1. Вы инициируете асинхронную операцию
//   2. Вы передаёте callback (обработчик завершения)
//   3. io_context управляет выполнением операций
//   4. Когда операция завершится — вызывается ваш callback
//
// Преимущества:
//   - Высокая производительность (один поток может обслуживать тысячи соединений)
//   - Без блокировок потоков
//   - Поддержка многопоточности через strand
//   - Работает на Windows, Linux, macOS
//
// Аналогия с Python:
//   Python asyncio  ↔  Boost.Asio
//   async/await     ↔  Asio корутины (C++20)
//   event loop      ↔  io_context.run()
//   asyncio.sleep() ↔  steady_timer
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 2: io_context — Основной класс Asio
// ─────────────────────────────────────────────────────────────────────────────
//
// io_context — это «движок» всех асинхронных операций Asio.
//
// ПРИМЕР КОДА (требует Boost):
//
//   #include <boost/asio.hpp>
//   namespace asio = boost::asio;
//
//   asio::io_context io;
//
//   // Запостить задачу на выполнение:
//   asio::post(io, []() {
//       std::cout << "Задача выполнена!" << std::endl;
//   });
//
//   // Запустить event loop (блокирует пока есть работа):
//   io.run();
//
//   // Многопоточный event loop:
//   std::vector<std::thread> threads;
//   for (int i = 0; i < 4; ++i) {
//       threads.emplace_back([&io]() { io.run(); });
//   }
//   for (auto& t : threads) t.join();
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 3: Таймеры — steady_timer
// ─────────────────────────────────────────────────────────────────────────────
//
// ПРИМЕР КОДА (требует Boost):
//
//   #include <boost/asio.hpp>
//   namespace asio = boost::asio;
//
//   asio::io_context io;
//   asio::steady_timer timer(io, std::chrono::seconds(2));
//
//   // Синхронное ожидание:
//   timer.wait();
//   std::cout << "2 секунды прошло" << std::endl;
//
//   // Асинхронное ожидание:
//   timer.async_wait([](const boost::system::error_code& ec) {
//       if (!ec) {
//           std::cout << "Асинхронный таймер!" << std::endl;
//       }
//   });
//   io.run();
//
//   // Периодический таймер:
//   void periodic_task(asio::steady_timer& t, int count) {
//       std::cout << "Тик " << count << std::endl;
//       if (count < 5) {
//           t.expires_after(std::chrono::seconds(1));
//           t.async_wait([&t, count](const boost::system::error_code& ec) {
//               if (!ec) periodic_task(t, count + 1);
//           });
//       }
//   }
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 4: TCP Сервер (синхронный)
// ─────────────────────────────────────────────────────────────────────────────
//
// ПРИМЕР КОДА (требует Boost):
//
//   #include <boost/asio.hpp>
//   namespace asio = boost::asio;
//   using tcp = asio::ip::tcp;
//
//   asio::io_context io;
//   tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));
//
//   std::cout << "Сервер запущен на порту 8080" << std::endl;
//
//   while (true) {
//       tcp::socket socket(io);
//       acceptor.accept(socket);  // Ожидание подключения (блокирует)
//
//       std::string message = "Hello from C++ Asio Server!\n";
//       asio::write(socket, asio::buffer(message));
//
//       // Читаем запрос:
//       asio::streambuf buf;
//       asio::read_until(socket, buf, '\n');
//       std::istream is(&buf);
//       std::string line;
//       std::getline(is, line);
//       std::cout << "Получено: " << line << std::endl;
//   }
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 5: TCP Клиент
// ─────────────────────────────────────────────────────────────────────────────
//
// ПРИМЕР КОДА (требует Boost):
//
//   #include <boost/asio.hpp>
//   namespace asio = boost::asio;
//   using tcp = asio::ip::tcp;
//
//   asio::io_context io;
//   tcp::resolver resolver(io);
//
//   // Разрешить имя хоста:
//   auto endpoints = resolver.resolve("example.com", "80");
//
//   tcp::socket socket(io);
//   asio::connect(socket, endpoints);
//
//   // HTTP запрос:
//   std::string request = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
//   asio::write(socket, asio::buffer(request));
//
//   // Читаем ответ:
//   asio::streambuf response;
//   asio::read_until(socket, response, "\r\n");
//   std::istream rs(&response);
//   std::string status_line;
//   std::getline(rs, status_line);
//   std::cout << "Ответ: " << status_line << std::endl;
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 6: Асинхронный эхо-сервер
// ─────────────────────────────────────────────────────────────────────────────
//
// ПРИМЕР КОДА (требует Boost):
//
//   #include <boost/asio.hpp>
//   namespace asio = boost::asio;
//   using tcp = asio::ip::tcp;
//
//   class Session : public std::enable_shared_from_this<Session> {
//       tcp::socket socket_;
//       char data_[1024];
//   public:
//       Session(tcp::socket socket) : socket_(std::move(socket)) {}
//
//       void start() { do_read(); }
//
//   private:
//       void do_read() {
//           auto self = shared_from_this();
//           socket_.async_read_some(asio::buffer(data_),
//               [this, self](boost::system::error_code ec, std::size_t length) {
//                   if (!ec) {
//                       do_write(length);
//                   }
//               });
//       }
//
//       void do_write(std::size_t length) {
//           auto self = shared_from_this();
//           asio::async_write(socket_, asio::buffer(data_, length),
//               [this, self](boost::system::error_code ec, std::size_t) {
//                   if (!ec) {
//                       do_read();  // Продолжаем читать
//                   }
//               });
//       }
//   };
//
//   class Server {
//       tcp::acceptor acceptor_;
//   public:
//       Server(asio::io_context& io, short port)
//           : acceptor_(io, tcp::endpoint(tcp::v4(), port)) {
//           do_accept();
//       }
//   private:
//       void do_accept() {
//           acceptor_.async_accept(
//               [this](boost::system::error_code ec, tcp::socket socket) {
//                   if (!ec) {
//                       std::make_shared<Session>(std::move(socket))->start();
//                   }
//                   do_accept();  // Продолжаем принимать соединения
//               });
//       }
//   };
//
//   asio::io_context io;
//   Server server(io, 8080);
//   io.run();
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// РАЗДЕЛ 7: Корутины с Asio (C++20)
// ─────────────────────────────────────────────────────────────────────────────
//
// С C++20 Asio поддерживает корутины через co_await:
//
// ПРИМЕР КОДА (требует Boost + C++20):
//
//   #include <boost/asio.hpp>
//   #include <boost/asio/co_spawn.hpp>
//   #include <boost/asio/detached.hpp>
//   namespace asio = boost::asio;
//
//   asio::awaitable<void> do_session(asio::ip::tcp::socket socket) {
//       char data[1024];
//       while (true) {
//           std::size_t n = co_await socket.async_read_some(
//               asio::buffer(data), asio::use_awaitable);
//           co_await asio::async_write(socket,
//               asio::buffer(data, n), asio::use_awaitable);
//       }
//   }
//
//   asio::awaitable<void> listener() {
//       auto executor = co_await asio::this_coro::executor;
//       asio::ip::tcp::acceptor acceptor(executor, {asio::ip::tcp::v4(), 8080});
//       while (true) {
//           auto socket = co_await acceptor.async_accept(asio::use_awaitable);
//           asio::co_spawn(executor, do_session(std::move(socket)), asio::detached);
//       }
//   }
//
//   asio::io_context io;
//   asio::co_spawn(io, listener(), asio::detached);
//   io.run();
// ─────────────────────────────────────────────────────────────────────────────

// Демонстрация без Boost: аналоги таймеров и многопоточности

class SimpleTimer {
public:
    // Аналог asio::steady_timer (упрощённый)
    static void wait(std::chrono::milliseconds duration) {
        std::this_thread::sleep_for(duration);
    }

    static void async_wait(std::chrono::milliseconds duration,
                           std::function<void()> callback) {
        std::thread([duration, callback]() {
            std::this_thread::sleep_for(duration);
            callback();
        }).detach();
    }
};

class SimpleTaskQueue {
    // Аналог asio::io_context (очень упрощённый)
    std::vector<std::function<void()>> tasks_;
    std::mutex mutex_;

public:
    void post(std::function<void()> task) {
        std::lock_guard<std::mutex> lock(mutex_);
        tasks_.push_back(std::move(task));
    }

    void run() {
        std::vector<std::function<void()>> to_run;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            to_run.swap(tasks_);
        }
        for (auto& task : to_run) {
            task();
        }
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Урок 15: Boost.Asio — Асинхронный I/O" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "ВАЖНО: Этот урок содержит документацию Boost.Asio." << std::endl;
    std::cout << "Демонстрационный код использует стандартную библиотеку C++." << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 1. Аналог io_context.post()
    // =========================================================================
    std::cout << "--- 1. Аналог asio::post() и io_context ---" << std::endl;

    SimpleTaskQueue queue;

    queue.post([]() { std::cout << "Задача 1 выполнена" << std::endl; });
    queue.post([]() { std::cout << "Задача 2 выполнена" << std::endl; });
    queue.post([]() { std::cout << "Задача 3 выполнена" << std::endl; });

    std::cout << "Задачи поставлены в очередь, запускаем..." << std::endl;
    queue.run();
    std::cout << std::endl;

    // =========================================================================
    // 2. Аналог steady_timer
    // =========================================================================
    std::cout << "--- 2. Аналог asio::steady_timer ---" << std::endl;

    std::cout << "Синхронное ожидание 100мс..." << std::endl;
    auto start = std::chrono::steady_clock::now();
    SimpleTimer::wait(std::chrono::milliseconds(100));
    auto elapsed = std::chrono::steady_clock::now() - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    std::cout << "Прошло: " << ms << "мс" << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 3. Аналог async_wait
    // =========================================================================
    std::cout << "--- 3. Аналог async_wait (неблокирующий таймер) ---" << std::endl;

    std::atomic<bool> done{false};

    SimpleTimer::async_wait(std::chrono::milliseconds(50), [&done]() {
        std::cout << "  [async] Таймер сработал в фоновом потоке!" << std::endl;
        done = true;
    });

    std::cout << "  Основной поток продолжает работу..." << std::endl;
    std::cout << "  Ожидаем завершения таймера..." << std::endl;

    while (!done) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << std::endl;

    // =========================================================================
    // 4. Многопоточность с задачами (аналог io_context + threads)
    // =========================================================================
    std::cout << "--- 4. Аналог многопоточного io_context ---" << std::endl;

    SimpleTaskQueue mt_queue;
    std::mutex cout_mutex;

    // Поставить несколько задач в очередь:
    for (int i = 1; i <= 5; ++i) {
        mt_queue.post([i, &cout_mutex]() {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "  Задача " << i << " в потоке "
                      << std::this_thread::get_id() << std::endl;
        });
    }

    // Выполнить задачи:
    mt_queue.run();
    std::cout << std::endl;

    // =========================================================================
    // 5. Обзор Asio API
    // =========================================================================
    std::cout << "--- 5. Обзор Boost.Asio API ---" << std::endl;
    std::cout << "Основные классы:" << std::endl;
    std::cout << "  asio::io_context         — движок событий" << std::endl;
    std::cout << "  asio::steady_timer       — таймер" << std::endl;
    std::cout << "  asio::ip::tcp::socket    — TCP сокет" << std::endl;
    std::cout << "  asio::ip::tcp::acceptor  — TCP сервер" << std::endl;
    std::cout << "  asio::ip::tcp::resolver  — DNS резолвер" << std::endl;
    std::cout << "  asio::ip::udp::socket    — UDP сокет" << std::endl;
    std::cout << "  asio::strand             — синхронизатор" << std::endl;
    std::cout << std::endl;
    std::cout << "Асинхронные операции:" << std::endl;
    std::cout << "  asio::async_write()      — асинхронная запись" << std::endl;
    std::cout << "  asio::async_read()       — асинхронное чтение" << std::endl;
    std::cout << "  socket.async_connect()   — асинхронное подключение" << std::endl;
    std::cout << "  acceptor.async_accept()  — асинхронный приём" << std::endl;
    std::cout << "  timer.async_wait()       — асинхронное ожидание" << std::endl;
    std::cout << std::endl;
    std::cout << "Компиляция:" << std::endl;
    std::cout << "  g++ -std=c++17 server.cpp -lboost_system -pthread" << std::endl;
    std::cout << "  clang++ -std=c++17 server.cpp -lboost_system -pthread" << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Урок 15 завершён!" << std::endl;
    std::cout << "  Следующий урок: Boost.Regex и сериализация" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "ДОМАШНЕЕ ЗАДАНИЕ:" << std::endl;
    std::cout << "1. Установите Boost и создайте простой TCP эхо-сервер" << std::endl;
    std::cout << "2. Реализуйте периодический таймер (каждую секунду)" << std::endl;
    std::cout << "3. Напишите HTTP клиент для загрузки страницы" << std::endl;
    std::cout << "4. Реализуйте многопоточный сервер с io_context + threads" << std::endl;
    std::cout << "5. Изучите корутины Asio (C++20 co_await)" << std::endl;

    return 0;
}
