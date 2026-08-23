#include<vector>
#include<algorithm>
#include<stdexcept>
#include<iostream>

template <typename T>
T maxOf(const std::vector<T>&v){
    if(v.empty()){
        throw std::invalid_argument("vector is empty");
    }
    auto it = std::max_element(v.begin(),v.end());
    return *it;

}

int main(){
    std::vector<double> dv = {1.3, 3.1, 2.7};
    std::vector<int> iv = {1, 3, 2};
    std::vector<int> ev;
    try{
        std::cout << "max = " <<  maxOf(dv) << std::endl;
    }catch (const std::exception& e){
        std::cout << "error: " << e.what() << std::endl;
    }
    try{
        std::cout << "max = " <<  maxOf(iv) << std::endl;
    }catch (const std::exception& e){
        std::cout << "error: " << e.what() << std::endl;
    }
    try{
        std::cout << "max = " <<  maxOf(ev) << std::endl;
    }catch (const std::exception& e){
        std::cout << "error: " << e.what() << std::endl;
    }

    return 0;
}