#include <iostream>
#include <cstdio>
#include <cstdint>
#include <memory>
#include <vector>

class B;

class A{
    public:
        ~A(){ std::cout << "~A\n"; }
        std::shared_ptr<B> b_;
    private:
};

class B{
    public:
        ~B(){ std::cout << "~B\n"; }
        std::weak_ptr<A> a_;
    private:
};

int main(){
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b_ = b;
    b->a_ = a;

    return 0;
}