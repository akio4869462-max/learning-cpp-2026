#include <iostream>
#include <string>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <atomic>
#include <thread>
#include <array>

enum class State{
    WaitSof, WaitLen, WaitPayload, WaitSum
};


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

class FrameParser {
    public:
        using Callback = void (*)(const uint8_t* payload, uint8_t len, void* ctx);

        FrameParser(Callback cb, void* ctx) : state_(), payload_{}, len_(0), got_(0), sum_(0), errors_(0), cb_(cb), ctx_(ctx) {}

        void feed(uint8_t byte){
            switch (state_) {
                case State::WaitSof:
                    if (byte == 0xAA) {
                        sum_ = byte;
                        state_ = State::WaitLen;
                    }
                    break;

                case State::WaitLen:
                    len_ = byte;
                    got_ = 0;
                    sum_ = static_cast<uint8_t>(sum_ + byte);
                    state_ = (len_ == 0) ? State::WaitSum : State::WaitPayload;
                    break;
                    
                case State::WaitPayload:
                    payload_[got_] = byte;
                    got_++;
                    sum_ = static_cast<uint8_t>(sum_ + byte);
                    state_ = (got_ == len_) ? State::WaitSum : State::WaitPayload;
                    break;

                case State::WaitSum:
                    if(sum_ == byte){
                        if(cb_) cb_(payload_.data(), len_, ctx_);
                    }else{
                        errors_++;
                    }
                    state_ = State::WaitSof;
                    break;
            }
        }

        unsigned errors() const {return errors_;}

    private:
        State state_;
        std::array<uint8_t,255> payload_{};
        uint8_t len_, got_, sum_, errors_;
        Callback cb_;
        void* ctx_;
};

void on_frame(const uint8_t* payload, uint8_t len, void* ctx) {
    (void)ctx;
    std::cout << "フレーム受信! len=" << (int)len << " データ: ";
    for (uint8_t i = 0; i < len; i++) {
        std::cout << std::hex << (int)payload[i] << " ";
    }
    std::cout << std::dec << std::endl;
}

void sender(RingBuf& rb, const std::vector<uint8_t>& payload) {
    uint8_t sum = 0;

    auto send_byte = [&](uint8_t b) {
        while (!rb.push(b)) {}   // 満杯なら成功するまでリトライ
    };

    send_byte(0xAA);                              // SOF
    sum = static_cast<uint8_t>(sum + 0xAA);

    uint8_t len = static_cast<uint8_t>(payload.size());
    send_byte(len);                                // LEN
    sum = static_cast<uint8_t>(sum + len);

    for (uint8_t b : payload) {                    // PAYLOAD
        send_byte(b);
        sum = static_cast<uint8_t>(sum + b);
    }

    send_byte(sum);                                // CHECKSUM
}

int main() {
    RingBuf rb(32);
    FrameParser fp(on_frame, nullptr);
    std::vector<uint8_t> payload = {0x10, 0x20, 0x30};

    std::thread t(sender, std::ref(rb), payload);

    size_t total_bytes = payload.size() + 3;   // SOF + LEN + PAYLOAD + CHECKSUM
    for (size_t i = 0; i < total_bytes; i++) {
        uint8_t b;
        while (!rb.pop(b)) {}   // データが来るまでリトライ
        fp.feed(b);
    }

    t.join();
    std::cout << "エラー数: " << fp.errors() << std::endl;
    return 0;
}
