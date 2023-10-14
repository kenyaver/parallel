#include <iostream>
#include <future>
#include <random>
#include <vector>
#include <numeric>

using namespace std;

static const int NUM = 10000000;

long long getDotProduct(vector<int>& v, vector<int>& w){
    auto vsize = v.size();

    auto fut1 = async([&]{
        return inner_product(&v[0], &v[vsize/4], &w[0], 0LL);
    });

    auto fut2 = async([&]{
        return inner_product(&v[vsize/4], &v[vsize/2], &w[vsize/4], 0LL);
    });

    auto fut3 = async([&]{
        return inner_product(&v[vsize/2], &v[vsize * 3/4], &w[vsize/2], 0LL);
    });

    auto fut4 = async([&]{
        return inner_product(&v[vsize * 3/4], &v[vsize], &w[vsize * 3/4], 0LL);
    });

    return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

int main(){
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution<int> dist(0, 100);

    vector<int> v, w;
    v.reserve(NUM);
    w.reserve(NUM);

    for(int i = 0; i < NUM; i++){
        v.push_back(dist(engine));
        w.push_back(dist(engine));
    }

    cout << "getDotProduct(v, w): " << getDotProduct(v, w) << '\n';
}