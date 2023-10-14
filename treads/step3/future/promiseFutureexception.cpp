#include <exception>
#include <iostream>
#include <future>
#include <thread>
#include <utility>
#include <string>

struct Div{
    void operator()(std::promise<int>&& intPromise, int a, int b){
        try{
            if(b == 0){
                std::string errMess = std::string("illegal divizion by zero");
                throw std::runtime_error(errMess);
            }
            intPromise.set_value(a/b);
        }
        catch(...){
            intPromise.set_exception(std::current_exception());
        }
    }
};

void executeDivision(int nom, int denom){
    std::promise<int> divPromise;
    std::future<int> divResult = divPromise.get_future();

    Div div;
    std::thread divThread(div, std::move(divPromise), nom, denom);

    try{
        std::cout
            << nom
            << '/'
            << denom
            << " = "
            << divResult.get()
            << '\n';
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << '\n';
    }

    divThread.join();
}


int main(){
    executeDivision(20, 0);
    executeDivision(20, 10);
}