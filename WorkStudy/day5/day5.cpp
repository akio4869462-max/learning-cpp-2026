#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

int main(){
    std::vector<double> v = {3.1, 1.2, 5.5, 2.0};

    std::sort(v.begin(), v.end());
    double total = std::accumulate(v.begin(), v.end(), 0.0);
    auto it = std::max_element(v.begin(), v.end());
    auto found = std::find(v.begin(), v.end(), 5.5);

    std::cout << "max = " << *it << ", sum = " << total << std::endl;

    for (const auto & x : v){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}