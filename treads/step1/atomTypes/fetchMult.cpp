#include <iostream>
#include <atomic>

template <typename T>

T fetch(std::atomic<T>& shar, T mult){
    T oldvalue = shar.load();
    while(!shar.compare_exchange_strong(oldvalue, oldvalue * mult));
    return oldvalue;
}

int main(){
    std::atomic<double> arr = 5;
    std::cout << arr << '\n';
    fetch(arr, 5.0);
    std:: cout << arr << '\n';
    return 0;
}