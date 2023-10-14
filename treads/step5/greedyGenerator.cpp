#include <iostream>
#include <vector>

std::vector<int> getNumber(int begin, int end, int inc = 1){
    std::vector<int> number;
    for(int i = begin; i < end; i+= inc){
        number.push_back(i);
    }

    return number;
}

int main(){
    const auto number = getNumber(-10, 10);

    for(auto i: number){
        std::cout << i << ' ';
    }
    std::cout << '\n';

    for(auto i: getNumber(0, 101, 5)){
        std::cout << i << ' ';
    }
    std::cout << '\n';
}