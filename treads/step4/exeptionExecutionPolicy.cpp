#include <algorithm>
#include <execution>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(){
    std::vector<int> vec{1, 2, 3, 4, 5};

    try{
        std::for_each(vec.begin(), vec.end(), [](int){
            throw std::runtime_error("Without execution policy");
        });
    }
    catch(const std::runtime_error& e){
        std::cout << e.what() << std::endl;
    }

    try{
        std::for_each(std::execution::seq, vec.begin(), vec.end(), [](int){
            throw std::runtime_error("With execution policy");
        });
    }
    catch(const std::runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    catch(...){
        std::cout << "catch all exceptions\n";
    }
}
