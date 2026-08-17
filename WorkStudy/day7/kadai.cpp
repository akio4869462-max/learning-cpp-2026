#include "kadai.h"
#include <iostream>

int main(){
    EchoLine e(1000);
    for(size_t i = 0;i < e.size(); ++i){
        e.set(i, std::sin(2.0 * 3.14159265 * i /100.0));
    }
    e.applyGain(10.0);
    EchoLine new_e = e.normalized();
    std::cout << "max = " <<  new_e.maxAmplitude() << std::endl;
}