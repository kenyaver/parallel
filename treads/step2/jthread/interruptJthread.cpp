#include <iostream>
#include <thread>
#include <chrono>

// using namespace std::literals;

int main(){
    std::jthread nonInterrutable([]{
        int counter = 0;
        while(counter < 10){
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "nonInterrutable " << counter << '\n';
            counter++;
        }
    });

    std::jthread interrutable([](std::stop_token stoken){
        int counter = 0;
        while(counter < 10){
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if(stoken.stop_requested()) return;
            std::cout << "interrutable " << counter << '\n';
            counter++;
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cerr << '\n';

    std::cerr << "main thread interrupts both jthread\n";
    nonInterrutable.request_stop();
    interrutable.request_stop();
}