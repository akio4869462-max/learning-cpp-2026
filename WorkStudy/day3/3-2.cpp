#include <memory>
#include <iostream>

// (1) 所有権をもらう版: 引数の型は unique_ptr<int> そのもの(値渡し)
void takeOwnership(std::unique_ptr<int> p) {
    std::cout << *p << std::endl;
} // 関数を抜けるとここで p (中身)が解放される

// (2) 借りるだけの版: 生ポインタで受け取る(所有権のやり取りはしない)
void borrow(const int* p) {
    std::cout << *p << std::endl;
}

int main(){
    auto a = std::make_unique<int>(42);

    borrow(a.get());
    takeOwnership(std::move(a));
}