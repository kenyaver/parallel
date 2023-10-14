#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

class spinLock{
    std::atomic_flag flag;

    public:
    spinLock(): flag(ATOMIC_FLAG_INIT){}

    void lock(){
        while(flag.test_and_set(std::memory_order_acquire));
    }

    void unlock(){
        flag.clear(std::memory_order_release);
    }
};

spinLock spin;

void workOnResource(){
    spin.lock();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "hello\n";
    // share resource
    spin.unlock();
}

int main(){
    std::thread t1(workOnResource);
    std::thread t2(workOnResource);

    t1.join();
    t2.join();
}