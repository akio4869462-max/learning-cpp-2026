#include <thread>
#include <mutex>
#include <iostream>

int counter = 0;
std::mutex m;

void worker(){
    for (int i = 0;i < 100000; ++i){
        // std::lock_guard<std::mutex> lock(m);
        ++counter;
    }
}

int main(){
    std::thread t1(worker), t2(worker);
    t1.join();
    t2.join();

    std::cout << counter << std::endl;

    return 0;
}