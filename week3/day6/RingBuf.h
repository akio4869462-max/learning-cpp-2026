#ifndef RINGBUF_H
#define RINGBUF_H

#include <cstdint>
#include <cstddef>
#include <vector>

class RingBuf {
public:
    explicit RingBuf(size_t capacity) : buf_(capacity + 1), head_(0), tail_(0) {}

    bool push(uint8_t byte) {
        if ((head_ + 1) % buf_.size() == tail_) {
            return false;
        }
        buf_[head_] = byte;
        head_ = (head_ + 1) % buf_.size();
        return true;
    }

    bool pop(uint8_t& out) {
        if (head_ == tail_) {
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
    size_t head_, tail_;
};

#endif
