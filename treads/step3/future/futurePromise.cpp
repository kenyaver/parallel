#include <future>
#include <iostream>
#include <thread>
#include <utility>

void product(std::promise<int>&& intPromise, int a, int b){
    intPromise.set_value(a * b);
}

void diver(std::promise<int>&& intPromise, int a, int b){
    intPromise.set_value(a / b);
}

int main(){
    int a = 20;
    int b = 10;

    std::promise<int> prodPromis;
    std::promise<int> divPromis;

    std::future<int> prodResult = prodPromis.get_future();
    std::future<int> divResult = divPromis.get_future();

    std::thread prodThread(product, std::move(prodPromis), a, b);
    std::thread divThread(diver, std::move(divPromis), a, b);

    // std::cout << prodResult.get() << ' ' << divResult.get() << '\n'; 

    prodThread.join();
    divThread.join();

    std::cout << prodResult.get() << ' ' << divResult.get() << '\n'; 

}