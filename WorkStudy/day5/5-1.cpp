#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
#include <iostream>

int main(){
    std::vector<double> signals(1000);
    for(size_t i = 0;i < signals.size(); ++i){
        double noise = (std::rand() % 100 / 500.0);
        signals[i] = std::sin(2.0 * 3.14159265 * i /100.0) + noise;
    }
    auto it = std::max_element(signals.begin(), signals.end());
    double total = std::accumulate(signals.begin(), signals.end(), 0.0);
    int n = std::count_if(signals.begin(), signals.end(), [](double x) { return x > 0.8; });

    std::cout << "max = " << *it << ", pos = " << (it - signals.begin()) << std::endl;
    std::cout << "ave = " << total / signals.size() << std::endl;
    std::cout << "num(>0.8) = " << n << std::endl;
}
