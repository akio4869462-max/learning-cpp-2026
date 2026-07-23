#include <iostream>
#include <string>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <atomic>
#include <thread>

class RingBuf{
public:
    explicit RingBuf(size_t capacity) : buf_(capacity+1), head_(0), tail_(0) {}

    bool push(uint8_t byte){
        if((head_ + 1) % buf_.size() == tail_){
            return false;
        }
        buf_[head_] = byte;
        head_ = (head_ + 1) % buf_.size();
        return true;
    }
    bool pop(uint8_t& out){
    if(head_ == tail_){
        return false;
    }
    out = buf_[tail_];
    tail_ = (tail_ + 1) % buf_.size();
    return true;
    }
    bool empty() const {
        return head_ == tail_;
    }


private:
    std::vector<uint8_t> buf_;
    std::atomic<size_t> head_, tail_;
};

void producer(RingBuf& rb, std::atomic<bool>& done, int total) {
    for (int i = 0; i < total; ++i) {
        uint8_t value = static_cast<uint8_t>(i % 256);
        while (!rb.push(value)) {
            // pushが成功するまで何もせずループ
        }
    }
    done = true;
}

int main(){
    RingBuf rb(16);
    std::atomic<bool> done = false;
    int total = 100000;
    uint8_t expected = 0;
    size_t received = 0;
    size_t mismatch = 0;

    std::thread t(producer, std::ref(rb), std::ref(done), total);

    while (!done.load() || !rb.empty()) {
        uint8_t out;
        if (rb.pop(out)) {
            if(out != expected) mismatch++;
            expected++;
            received++;
        }
    }
    std::cout << "(received, mismatch): (" << received << ", " << mismatch << ")" << std::endl;

    t.join();

    return 0;
}
