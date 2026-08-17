#include <stdexcept>
#include <iostream>

double safeDivide(double a, double b){
    if(b == 0.0){
        throw std::invalid_argument("division by zero");
    }
    return a / b;
}

int main(){
    try{
        std::cout << safeDivide(10.0, 0.0) << std::endl;
    } catch (const std::exception& e){
        std::cout << "error: " << e.what() << std::endl;
    }
    return 0;
}
