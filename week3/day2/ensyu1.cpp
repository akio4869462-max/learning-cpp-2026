#include <cstdint>
#include <atomic>
#include <thread>
#include <chrono>
#include <iostream>

std::atomic<uint32_t> tick_count;
std::atomic<bool> running;

void increment(){
    while(running){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        tick_count.fetch_add(1, std::memory_order_relaxed);
    }
}

int main(){
    uint32_t last_100ms = 0;
    uint32_t last_1s = 0;
    running = true;
    std::thread t(increment);
    while(tick_count < 3000){
        if (tick_count - last_100ms >= 100) {
            std::cout << "100ms経過" << std::endl;   // 実際の処理はここ
            last_100ms = tick_count;                  // (b)方式: 現在値にスナップ
        }

        if (tick_count - last_1s >= 1000) {
            std::cout << "1s経過" << std::endl;   // 実際の処理はここ
            last_1s = tick_count;                  // (b)方式: 現在値にスナップ
        }
    }

    running = false;
    t.join();
}