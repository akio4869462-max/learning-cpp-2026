#include <vector>
#include <iostream>
#include <algorithm>

int main(){
    int threshold = 10;
    std::vector<int> v = {5, 15, 8, 20, 3};
    auto count = std::count_if(v.begin(), v.end(), [threshold](int x) { return x > threshold; });

    std::cout << count << std::endl;
}
