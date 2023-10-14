#include <utility>
#include <future>
#include <iostream>
#include <thread>
#include <deque>

class sumUp{
    public:
    long long int operator()(int beg, int end){
        long long int sum{0};
        for(int i = beg; i < end; i++){
            sum += i;
        }
        return sum;
    }
};

int main(){
    sumUp s1;
    sumUp s2;
    sumUp s3;
    sumUp s4;

    std::packaged_task<int(int, int)> sumTask1(s1);
    std::packaged_task<int(int, int)> sumTask2(s2);
    std::packaged_task<int(int, int)> sumTask3(s3);
    std::packaged_task<int(int, int)> sumTask4(s4);

    std::future<int> sumRes1 = sumTask1.get_future();
    std::future<int> sumRes2 = sumTask2.get_future();
    std::future<int> sumRes3 = sumTask3.get_future();
    std::future<int> sumRes4 = sumTask4.get_future();

    std::deque<std::packaged_task<int(int, int)>> allTask;
    allTask.push_back(std::move(sumTask1));
    allTask.push_back(std::move(sumTask2));
    allTask.push_back(std::move(sumTask3));
    allTask.push_back(std::move(sumTask4));

    int begin{1};
    int increment{2500};
    int end = begin + increment;
    while(not allTask.empty()){
        std::packaged_task<int(int, int)> myTask = std::move(allTask.front());
        allTask.pop_front();
        std::thread sumThread(std::move(myTask), begin, end);
        begin = end;
        end += increment;
        sumThread.detach();
    }

    auto sum = sumRes1.get() + sumRes2.get() + sumRes3.get() + sumRes4.get();

    std::cout << sum << '\n';
}