// синхронизация потоков при помощи atomic bool. по сути, то же самое, что с флагом, но другой тип данных))

#include <thread>
#include <atomic>
#include <iostream>
#include <vector>

std::vector<int> myVec;

std::atomic<bool> atomBool = false;

void prepareWork(){
    myVec.insert(myVec.end(), {0, 1, 0, 3});
    std::cout << "sender: Data prepared\n";
    atomBool.store(true);
    atomBool.notify_one();
}

void completeWork(){
    std::cout << "waiter: wait a data\n";
    atomBool.wait(false);
    myVec[2] = 2;
    std::cout << "waiter: complete the work\n";

    for(auto i: myVec){
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int main(){
    std::thread t1(prepareWork);
    std::thread t2(completeWork);

    std::cout << '\n';

    t1.join();
    t2.join();

    std::cout << '\n';

    return 0;
}