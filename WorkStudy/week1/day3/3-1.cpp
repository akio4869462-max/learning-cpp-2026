#include <stdexcept>
#include <iostream>
#include <vector>

int main(){
    try
    {
        /* code */
        // double* a = new double[1000];
        std::vector<double> a(1000);
        throw std::runtime_error("test");
        // delete[] a;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}