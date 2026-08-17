#include <iostream>

int main(){
    double a[3];
    double* p = a;
    *p = 1.0;
    *(p+1) = 2.0;
    *(p+2) = 3.0;

    std::cout << *p << ", " << *(p+1) << ", " << *(p+2) << std::endl;
    
    double* h = new double[3];
    *h = 1.0;
    *(h+1) = 2.0;
    *(h+2) = 3.0;

    std::cout << *h << ", " << *(h+1) << ", " << *(h+2) << std::endl;

    delete[] h;
}