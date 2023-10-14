#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> flag = 0;

int main(){
    std::cout << "hardware concurency: " << std::thread::hardware_concurrency() << '\n';

    std::thread t1([]{
        std::cout << "t1_id: " << std::this_thread::get_id() << '\n';
        flag.store(1);
        flag.notify_one();
    });

    std::thread t2([]{
        while(flag.load() != 1){}
        std::cout << "t2_id: " << std::this_thread::get_id() << '\n';
        flag.store(2);
        flag.notify_one();
    });

    while(flag.load() != 2){}
    std::cout << std::endl;

    std::cout << "from MAIN thread t1_id and t2_id: " << t1.get_id() << ' ' << t2.get_id() << '\n';

    std::cout << '\n';

    std::swap(t1, t2);

    std::cout << "from MAIN thread t1_id and t2_id: " << t1.get_id() << ' ' << t2.get_id() << '\n';

    std::cout << "id of MAIN thread: " << std::this_thread::get_id() << '\n';

    std::cout << "t1.joinable(): " << t1.joinable() << '\n';

    t1.join();
    t2.join();

    std::cout << "t1.joinable(): " << t1.joinable() << '\n';
    std::cout << '\n';
    return 0;
}