#include <iostream>
#include <future>


int main(){
    int s1{0};
    int s2{0};
    int s3{0};
    int s4{0};
    int sum;
    auto fut1 = std::async(std::launch::async, [&]{
        for(int i = 0; i < 2500; i++){
            s1 += i;
        }
        return s1;
    });

    auto fut2 = std::async(std::launch::async, [&]{
        for(int i = 2500; i < 5000; i++){
            s2 += i;
        }
        return s2;
    });

    auto fut3 = std::async(std::launch::async, [&]{
        for(int i = 5000; i < 7500; i++){
            s3 += i;
        }
        return s3;
    });

    auto fut4 = std::async(std::launch::async, [&]{
        for(int i = 7500; i <= 10000; i++){
            s4 += i;
        }
        return s4;
    });

    sum = fut1.get() + fut2.get() + fut3.get() + fut4.get();

    std::cout << sum << '\n';


}