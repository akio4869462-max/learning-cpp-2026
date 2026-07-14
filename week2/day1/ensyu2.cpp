#include <iostream>
#include <string>
#include <cstdio>
#include <cstdint>
#include <vector>

class RingBuf{
public:
    explicit RingBuf(size_t capacity) : buf_(capacity), head_(0), tail_(0), count_(0) {}

    bool push(uint8_t byte){
        if(count_ == buf_.size()){
            return false;
        }
        buf_[head_] = byte;
        head_ = (head_ + 1) % buf_.size();
        count_++;
        return true;
    }
    bool pop(uint8_t& out){
    if(count_ == 0){
        return false;
    }
    out = buf_[tail_];
    tail_ = (tail_ + 1) % buf_.size();
    count_--;
    return true;
    }

    size_t count() const{
        return count_;
    }

private:
    std::vector<uint8_t> buf_;
    size_t head_, tail_, count_;
};

int main(){
    RingBuf rb(3);
    std::cout << std::boolalpha;
    std::cout << rb.push(1) << " " << rb.push(2) << " " << rb.push(3) << " " << rb.push(4) << std::endl;  // 最後だけfalseのはず

    uint8_t out;
    while (rb.pop(out)) {
        std::cout << (int)out << " ";
    }
    std::cout << std::endl;

    return 0;
}
