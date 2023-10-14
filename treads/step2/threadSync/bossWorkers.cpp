#include <iostream>
#include <thread>
#include <latch>
#include <mutex>


std::latch workDone(6);
std::latch goHome(1);

std::mutex cMut;

void synchrozedOut(const std::string& s){
    std::lock_guard<std::mutex> lck(cMut);
    std::cout << s;
}

class Worker{
    private:
    std::string name;

    public:
    Worker(std::string n): name(n) { };

    void operator() (){
        synchrozedOut(name + ": Work done!\n");
        workDone.count_down();

        goHome.wait();
        synchrozedOut(name + ": Good bye!\n");
    }
};

int main(){
    std::cout << "BOSS: go work!\n";

    Worker herb("herb");
    std::thread herbWork(herb);

    Worker scott("scott");
    std::thread scottWork(scott);

    Worker bjarne("bjarne");
    std::thread bjarneWork(bjarne);

    Worker andrei("andrei");
    std::thread andreiWork(andrei);

    Worker andrew("andrew");
    std::thread andrewWork(andrew);

    Worker devid("devid");
    std::thread devidWork(devid);

    workDone.wait();

    std::cout << "BOSS: go home!\n";

    goHome.count_down();

    herbWork.join();
    scottWork.join();
    bjarneWork.join();
    andreiWork.join();
    andrewWork.join();
    devidWork.join();
}
