#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>



int main(){
    std::vector<int> vec {0, 1, 2, 3, 4};

    std::cout << vec.size();

    return 0;
}