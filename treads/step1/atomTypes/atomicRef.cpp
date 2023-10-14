#include <iostream>
#include <atomic>
#include <random>
#include <thread>
#include <vector>

struct expToCopy{
    int counter= 0;
};

int getRandom(int begin, int end){
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> uniform(begin, end);

    return uniform(engine);
}

void count(expToCopy& exp){
    std::vector<std::thread> v;
    std::atomic_ref<int> counter = exp.counter;

    for(int n = 0; n < 10; n++){
        v.emplace_back([&counter]{
        auto randNumb = getRandom(100, 200);
        for(int j = 0; j < randNumb; ++j){
            ++counter;
        }
        });
    }

    for(auto& t: v){
        t.join();
    }
}

int main(){
    std::cout << '\n';

    expToCopy exp;
    count(exp);
    std::cout << "exp.counter: " << exp.counter << '\n';

    std::cout << '\n';
}