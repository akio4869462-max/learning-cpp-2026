#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, -999, 2, 3, -999, 4};

    auto new_end = std::remove_if(v.begin(), v.end(), [](int x) { return x == -999; });
    v.erase(new_end, v.end());
    
    std::cout << "サイズ: " << v.size() << std::endl;
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}