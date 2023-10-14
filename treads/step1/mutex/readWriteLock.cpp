#include <mutex>
#include <thread>
#include <iostream>
#include <shared_mutex>
#include <map>
#include <string>
#include <chrono>

std::map<std::string, int> telebook{
    {"artem", 2004}, {"kostik", 2005}, {"stepan", 2003}
};

std::shared_timed_mutex tbMutex;

void addToTelebook(const std::string& name, int number){
    std::lock_guard<std::shared_timed_mutex> writer(tbMutex);
    std::cout << "\nSTARTING UPDATE " << name;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    telebook[name] = number;
    std::cout << " ... ENDING UPDATE " << name << '\n';
}

void printNumber(const std::string& name){
    std::shared_lock<std::shared_timed_mutex> reader(tbMutex);
    auto search = telebook.find(name);
    if(search != telebook.end()){
        std::cout << search -> first << ": " << search -> second << '\n';
    } else {
        std::cout << "not found!\n";
    }
    // std::cout << name << ": " << telebook[name] << '\n';
}

int main(){
    std::thread r1([]{
        printNumber("artem");
    });

    std::thread r2([]{
        printNumber("stepan");
    });

    std::thread w1([]{
        addToTelebook("Mila", 2002);
    });

    std::thread r3([]{
        printNumber("artem");
    });

    std::thread r4([]{
        printNumber("stepan");
    });

    std::thread r5([]{
        printNumber("kostik");
    });

    std::thread r6([]{
        printNumber("Mila");
    });

    r1.join();
    r2.join();
    w1.join();
    r3.join();
    r4.join();
    r5.join();
    r6.join();
    
}