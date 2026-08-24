#include <cassert>
#include <stdexcept>
#include <iostream>
#include "kadai.h"

int main(){
    // (1) 正常系
    EchoLine e(3);
    e.set(0, 2.0);
    e.applyGain(2.0);
    assert(e.get(0) == 4.0);

    // (2) 境界値
    EchoLine empty(0);
    assert(empty.maxAmplitude() == 0.0);

    // (3) 異常系
    try{
        EchoLine e(3);
        e.get(5);
    }catch (const std::exception& e){
        std::cout << "error: " << e.what() << std::endl;
    }
}