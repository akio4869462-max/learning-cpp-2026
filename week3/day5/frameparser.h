#ifndef FRAMEPURSER_H
#define FRAMEPURSER_H

#include <cstdint>
#include <array>

enum class State{
    WaitSof, WaitLen, WaitPayload, WaitSum
};

class FrameParser {
    public:
        using Callback = void (*)(const uint8_t* payload, uint8_t len, void* ctx);

        FrameParser(Callback cb, void* ctx) : state_(), payload_{}, len_(0), got_(0), sum_(0), errors_(0), cb_(cb), ctx_(ctx) {}

        inline void feed(uint8_t byte, uint32_t tick) {
            if (state_ != State::WaitSof && (tick - last_tick_) >= 100) {
                state_ = State::WaitSof;   // タイムアウト、途中のフレームを破棄
            }
            last_tick_ = tick;             // 今回の受信tickを記録
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
        uint32_t last_tick_;
        Callback cb_;
        void* ctx_;
};

#endif