// большую роль играет использование дороостоящих операций. если есть возможность - атомарные переменные и блокировщики в циклах не использовать
// блокировщики в линукс работают медленнее всех остальных вариантов использования синхронизации (ситуация переворачивается наоборот на windows)


#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>
#include <thread>
#include <utility>
#include <atomic>
#include <future>

constexpr long long size = 1000000;

constexpr long long fir = 250000;
constexpr long long sec = 500000;
constexpr long long thi = 750000;
constexpr long long fou = 1000000;

thread_local unsigned long long sumt;

// std::mutex mut;

void summer(std::vector<int> val, std::promise<unsigned long long>& mainSum, unsigned long long beg, unsigned long long end){
    unsigned long long sumth{0};
    for(auto i = beg; i < end; i++){
        // std::lock_guard<std::mutex> lock(mut);
        // mainSum.fetch_add(val[i], std::memory_order_relaxed);
        sumth += val[i];
    }

    // std::lock_guard<std::mutex> lock(mut);
    // mainSum.fetch_add(sumt, std::memory_order_relaxed);
    mainSum.set_value(sumth);
}


int main(){
    std::vector<int> value;
    value.reserve(size);

    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution udist(1, 10);

    for(auto i = 0; i < size; i++){
        value.push_back(udist(engine));
    }

    std::promise<unsigned long long> sum1;
    std::promise<unsigned long long> sum2;
    std::promise<unsigned long long> sum3;
    std::promise<unsigned long long> sum4;

    auto fut1 = sum1.get_future();
    auto fut2 = sum2.get_future();
    auto fut3 = sum3.get_future();
    auto fut4 = sum4.get_future();

    auto mom = std::chrono::steady_clock::now();

    std::thread t1(summer, std::ref(value), std::ref(sum1), 0, fir);
    std::thread t2(summer, std::ref(value), std::ref(sum2), fir, sec);
    std::thread t3(summer, std::ref(value), std::ref(sum3), sec, thi);
    std::thread t4(summer, std::ref(value), std::ref(sum4), thi, fou);

    

    auto summ = fut1.get() + fut2.get() + fut3.get() + fut4.get();

    std::chrono::duration<double> dur = std::chrono::steady_clock::now() - mom;

    std::cout << "sum: " << summ << std::endl;
    std::cout << "time: " << dur.count() << std::endl;
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}