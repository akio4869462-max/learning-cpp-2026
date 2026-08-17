#include <iostream>

void doubleIt(double& x){
    x *= 2;
}

void doubleIt(double* x){
    *x *= 2;
}

int main(){
    double x = 2.5, y=3.5;

    doubleIt(x);
    doubleIt(&y);

    std::cout << x << ", " << y << std::endl;
}

/*
参照渡しをするかポインタで渡すか。
参照はnullptrにならないメリットがあるが記述の時点でコピーなのか参照なのかがわからない。
ポインタは記述時点でアドレスを渡しているので書き換える可能性がわかりやすいが、nullptrに注意が必要
*/