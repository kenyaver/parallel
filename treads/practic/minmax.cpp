#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <future>
#include <array>

void min(std::vector<int> vec, std::promise<int>&& mini){
    int m = vec[0];
    for(auto i: vec){
        if(i < m){
            m = i;
        }
    }

    mini.set_value(m);
}

void max(std::vector<int> vec, std::promise<int>&& maxa){
    int m = vec[0];
    for(auto i: vec){
        if(i > m){
            m = i;
        }
    }

    maxa.set_value(m);
}


int main(){
    std::vector<int> vector{9, 2, 8, 3, 7, 0, 4, 6, 5, 1};
    std::array<int, 2> minmax;
    
    std::promise<int> mini;
    std::promise<int> maxa;
    
    auto futmin = mini.get_future();
    auto futmax = maxa.get_future();

    std::thread t1(min, vector, std::move(mini));
    std::thread t2(max, vector, std::move(maxa));

    minmax[0] = futmin.get();
    minmax[1] = futmax.get();
    

    t1.join();
    t2.join();

    
    for(auto i: minmax){
        std::cout << i << ' ';
    }
}