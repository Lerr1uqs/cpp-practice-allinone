#include <iostream>
#include <future>
#include <thread>

// A future or promise represents the future value of an asynchronous task.
/*
std::future：作为异步操作的消费者。
std::promise：作为异步操作的生产者。
*/
int main() {
    auto promise = std::promise<std::string>();

    auto producer = std::thread([&]
    {
        promise.set_value("Hello World");
        std::cout << "promise set value" << std::endl;
        std::cout << "sleep for 3 secs" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    });

    auto future = promise.get_future();

    auto consumer = std::thread([&]
    {
        // 这里立刻获得这个get值 不需要等待
        std::cout << future.get() << std::endl;
    });

    producer.join();
    consumer.join();

    return 0;
}