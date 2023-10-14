#include <iostream>
#include <thread>

void hellofunc(){
    std::cout << "hello from func\n";
}

class hellofuncObj{
    public:
    void operator()() const{
        std::cout << "hello from funcObj\n";
    }
};

int main(){
    std::cout << '\n';

    std::thread t1(hellofunc);

    hellofuncObj hfo;
    std::thread t2(hfo);

    std::thread t3([]{
        std::cout << "hello from lambda\n";
    });

    t1.join();
    t2.join();
    t3.join();
}