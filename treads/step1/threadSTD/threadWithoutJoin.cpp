#include <iostream>
#include <thread>

int main(){
    std::thread t1([]{
        std::cout << std::this_thread::get_id() << '\n';
    });

    t1.join();
    return 0;
}