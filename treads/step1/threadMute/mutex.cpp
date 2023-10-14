#include <thread>
// #include <atomic>
#include <chrono>
#include <mutex>
#include <iostream>

std::mutex mut;

void workOnResource(){
    mut.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "hello\n";
    mut.unlock();
}

int main(){
    std::thread t1(workOnResource);
    std::thread t2(workOnResource);

    t1.join();
    t2.join();
    return 0;
}


//по факту, описан еще 1 способ блокировки потоков. только уже при помощи мьютексов. такой способ создает меньше нагрузки на процессор.