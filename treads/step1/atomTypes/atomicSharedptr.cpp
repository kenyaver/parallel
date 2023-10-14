#include <atomic>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

int main(){
    std::cout << '\n';

    std::atomic<std::shared_ptr<std::string>> sharString(std::make_shared<std::string>("zero"));
    
    std::thread t1([&sharString]{
        sharString.store(std::make_shared<std::string>(*sharString.load() + " one"));
    });

    std::thread t2([&sharString]{
        sharString.store(std::make_shared<std::string>(*sharString.load() + " two"));
    });

    std::thread t3([&sharString]{
        sharString.store(std::make_shared<std::string>(*sharString.load() + " three"));
    });

    std::thread t4([&sharString]{
        sharString.store(std::make_shared<std::string>(*sharString.load() + " four"));
    });

    std::thread t5([&sharString]{
        sharString.store(std::make_shared<std::string>(*sharString.load() + " five"));
    });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::cout << *sharString.load() << '\n';
    return 0;
}