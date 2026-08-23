#include <stdexcept>
#include <iostream>

double pulseEchoTime(double depthCm){
    if(depthCm < 0.0){
        throw std::invalid_argument("depth is minues");
    }
    return 2 * (depthCm / 100) / 1540;
}

int main(){
    try{
        std::cout << pulseEchoTime(125.0) << std::endl;
    }catch (const std::exception& e){
        std::cout << "error: " << e.what() << std::endl;
    }
    try{
        std::cout << pulseEchoTime(-125.0) << std::endl;
    }catch (const std::exception& e){
        std::cout << "error: " << e.what() << std::endl;
    }
    return 0;
}