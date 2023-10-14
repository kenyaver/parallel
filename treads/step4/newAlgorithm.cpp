#include <algorithm>
#include <execution>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>

int main(){
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};

    // for_each_n:
    std::for_each_n(
        std::execution::par,
        vec.begin(),
        5,
        [](int& arg){arg *= arg; }
    );
    
    std::cout << "for_each_n: ";
    for(auto i: vec){
        std::cout << i << ' ';
    }
    std:: cout << std::endl;

    // exclusive and inclisive scans:
    std::vector<int> vecsive{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::exclusive_scan(
        std::execution::par,
        vecsive.begin(), vecsive.end(), vecsive.begin(), 1,
        [](int fir, int sec){ return fir * sec; }
    );

    std::cout << "exclusive_scan: ";
    for(auto i: vecsive){
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    std::vector<int> sive{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::inclusive_scan(
        std::execution::par,
        sive.begin(), sive.end(), sive.begin(), [](int fir, int sec){ return fir * sec; }, 1
    );

    std::cout << "inclusive_scan: ";
    for(auto i: sive){
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    // transform_inclusive_scan and transform_exclusive_scan:
    std::vector<int> tvec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> tvec2(tvec.size());
    std::transform_exclusive_scan(
        std::execution::par,
        tvec.begin(), tvec.end(), tvec2.begin(), 0,
        [](int fir, int sec){ return fir * sec; },
        [](int arg){ return arg * arg; }
    );

    std::cout << "transform_exclusive_scan: ";
    for(auto i: tvec2){
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    
}