#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>

class spinlock{
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

    public:
    void lock(){
        while(flag.test_and_set() );
    }

    void unlock(){
        flag.clear();
    }

    void ptint(){
        std::cout << "hello\n";
    }
};

spinlock spin;

void workOnResource(){
    spin.lock();
    // shared resource
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "hello\n";
    // spin.ptint();
    spin.unlock();
}

int main(){
    std::thread t1(workOnResource);
    std::thread t2(workOnResource);

    t1.join();
    t2.join();

    return 0;
}

// данный код является блокировщиком и по сути делает то же самое, что и мьютекс. однако использовать такую блокировку будет выгодно только в очень коротких 
// по времени промежутках. как правило, валиднее использовать мьютексы, либо подобный блокировщик, вытекающий в мьютекс.