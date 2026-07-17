#include <iostream>
#include <cstdint>
#include <array>
#include <vector>

enum class State{
    WaitSof, WaitLen, WaitPayload, WaitSum
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

int main() {
    FrameParser parser(on_frame, nullptr);

    std::cout << "--- 正常フレーム ---" << std::endl;
    uint8_t ok_frame[] = {0xAA, 0x02, 0x10, 0x20, 0xDC};
    for (uint8_t b : ok_frame) parser.feed(b);

    std::cout << "--- チェックサム不一致 ---" << std::endl;
    uint8_t bad_checksum[] = {0xAA, 0x02, 0x10, 0x20, 0xFF};
    for (uint8_t b : bad_checksum) parser.feed(b);

    std::cout << "--- ゴミ混入 ---" << std::endl;
    uint8_t gab_checksum[] = {0x02, 0x10, 0xDD, 0xAA, 0x02, 0x10, 0x20, 0xDC};
    for (uint8_t b : gab_checksum) parser.feed(b);
    
    std::cout << "--- ペイロードなし ---" << std::endl;
    uint8_t empty_payload[] = {0xAA, 0x00, 0xAA};
    for (uint8_t b : empty_payload) parser.feed(b);

    std::cout << "--- ペイロード最大(255) ---" << std::endl;
    std::vector<uint8_t> big_frame;
    uint8_t sum = 0;

    big_frame.push_back(0xAA);
    sum = static_cast<uint8_t>(sum + 0xAA);

    big_frame.push_back(255);
    sum = static_cast<uint8_t>(sum + 255);

    for (int i = 0; i < 255; i++) {
        uint8_t val = static_cast<uint8_t>(i);
        big_frame.push_back(val);
        sum = static_cast<uint8_t>(sum + val);
    }

    big_frame.push_back(sum);   // 最後に計算済みのチェックサムを追加

    for (uint8_t b : big_frame) parser.feed(b);

    std::cout << "エラー数: " << parser.errors() << std::endl;   // このあたりで1のはず

    return 0;
}
