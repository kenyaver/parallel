#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

struct criticalData{
    std::mutex mut;
};

void deadlock(criticalData& a, criticalData& b){
    std::unique_lock<std::mutex> guard1(a.mut, std::defer_lock);
    std::cout << "Thread: " << std::this_thread::get_id() << " first mutex\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::unique_lock<std::mutex> guard2(b.mut, std::defer_lock);
    std::cout << "Thread: " << std::this_thread::get_id() << " second mutex\n";

    std::cout << "Thread: " << std::this_thread::get_id() << " get both mutexes\n";
    std::lock(guard1, guard2);

    // do something with a and b
}   

int main(){
    criticalData c1;
    criticalData c2;

    std::thread t1([&]{
        deadlock(c1, c2);
    });

    std::thread t2([&]{
        deadlock(c2, c1);
    });

    t1.join();
    t2.join();
}