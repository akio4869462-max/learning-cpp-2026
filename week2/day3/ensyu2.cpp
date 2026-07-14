#include <iostream>
#include <cstdio>
#include <cstdint>
#include <memory>
#include <vector>

class Base{
    public:
        virtual ~Base(){
            std::cout << "~Base()" << std::endl;
        }
};

class Derived : public Base{
    public:
        Derived() {data_ = new int[100];}
        ~Derived() {delete[] data_; std::cout << "~Derived (freed)" << std::endl;}

    private:
        int* data_;
};

int main(){
    std::unique_ptr<Base> base;
    base = std::make_unique<Derived>();
}