#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

std::mutex cmute;

class Worker{
    private:
    std::string name;
    
    public:
    Worker(std::string n): name(n){};

    void operator()(){
        for(int i = 1; i <= 3; i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            cmute.lock();
            std::cout << name << ": work " << i << " done!!!\n";
            cmute.unlock(); 
        }
    }
};

int main(){
    std::cout << "Boss: let`s start working!\n";

    std::thread herb = std::thread(Worker("Herb"));
    std::thread andrei = std::thread(Worker("andrei"));
    std::thread scott = std::thread(Worker("scott"));
    std::thread bjarne = std::thread(Worker("bjarne"));
    std::thread bart = std::thread(Worker("bart"));
    std::thread jenne = std::thread(Worker("jenne"));

    herb.join();
    andrei.join();
    scott.join();
    bjarne.join();
    bart.join();
    jenne.join();

    std::cout << "let`s go home!\n";
}