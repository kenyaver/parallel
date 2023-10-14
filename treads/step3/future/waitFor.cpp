#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

void getAnswer(std::promise<int> prom){
    std::this_thread::sleep_for(3s);
    prom.set_value(42);
}

int main(){
    std::promise<int> answer;
    auto fut = answer.get_future();

    std::thread ans(getAnswer, std::move(answer));

    std::future_status status{};
    
    do{
        status = fut.wait_for(0.2s);
        std::cout << "...doing something else...\n";
    } while(status != std::future_status::ready);

    std:: cout << "\nthe answer is " << fut.get() << '\n';

    ans.join();
}