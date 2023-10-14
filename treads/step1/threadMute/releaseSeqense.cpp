#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>

std::atomic<int> atom = 0;
int some = 0;

void writer(){
    some = 2011;
    atom.store(2, std::memory_order_release);
}

void reader(){
    while(!(atom.fetch_sub(1, std::memory_order_acquire) > 0)){
        // std::cout << atom << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "something shared: " << some << '\n';
}

int main(){

    std::thread t1(writer);
    std::thread t2(reader);
    std::thread t3(reader);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "atom: " << atom << '\n';
}