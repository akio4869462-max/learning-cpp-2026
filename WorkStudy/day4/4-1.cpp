#include<vector>
#include<iostream>

class Tracer {
public:
    Tracer() { std::cout << "Tracer()\n"; }
    ~Tracer() { std::cout << "~Tracer()\n"; }
    Tracer(const Tracer&) { std::cout << "copyTracer()\n"; }
    Tracer(Tracer&&) noexcept { std::cout << "moveTracer()\n"; }
};

int main(){
    Tracer a;                          // コンストラクタとデストラクタ
    Tracer b = a;                      // コピー、デストラクタ
    Tracer c = std::move(a);           // ムーブ、デストラクタ
    std::vector<Tracer> v;
    v.push_back(Tracer());             // コンストラクタ
}
