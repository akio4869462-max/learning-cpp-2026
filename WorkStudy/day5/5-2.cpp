#include <algorithm>
#include <vector>
#include <iostream>

int main(){
    std::vector<double> v(5);
    std::vector<double> w(5);
    v = {1.0, 3.2, 2.5, 4.0, 0.4};
    w = {1.0, 3.2, 2.5, 4.0, 0.4};

    std::transform(v.begin(), v.end(), v.begin(), [](double x){ return x*2;});
    for(auto& x : v){
        std::cout << x << std::endl;
    }
    for(auto& y : w){
        y *= 2;
        std::cout << y << std::endl;
    }
}

//全要素にたいして同じことをしているのがわかるのはtransformだと感じた