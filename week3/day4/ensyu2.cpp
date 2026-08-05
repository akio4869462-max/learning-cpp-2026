#include <array>
#include <cstddef>
#include <algorithm>
#include <fstream>
#include <random>
#include <iostream>

// Q8.8: 上位8bit整数部、下位8bit小数部
using q8_8 = int16_t;
constexpr q8_8 to_q8_8(float f) { return static_cast<q8_8>(f * 256.0f); }
constexpr q8_8 q_mul(q8_8 a, q8_8 b) {
    return static_cast<q8_8>((static_cast<int32_t>(a) * b) >> 8);   // 中間は32bitで(オーバーフロー対策)
}

class MeanQ88 {
public:
    q8_8 update(q8_8 value) {
        // シフト処理はMeanと全く同じ
        for(size_t i=num_;i>0;i--){
            if(i < 5) buf_[i] = buf_[i-1];
        }
        buf_[0] = value;
        if(num_<5) num_++;
        int32_t sum = 0;                    // ← 合計はint32_tで(オーバーフロー対策、4-1と同じ発想)
        for (const auto& b : buf_) sum += b;
        // ...
        return static_cast<q8_8>(sum / num_);   // 普通の整数除算でOK
    }
private:
    std::array<q8_8, 5> buf_{};
    size_t num_ = 0;
};


class Mean{
    public:
        double update(double value) {
            double result = 0.0;
            for(size_t i=num_;i>0;i--){
                if(i < 5) buf_[i] = buf_[i-1];
            }
            buf_[0] = value;
            for(const auto& b : buf_){
                result += b;
            }
            if(num_<5) num_++;
            result /= num_;
            return result;
        };
    private:
        std::array<double, 5> buf_{};
        size_t num_ = 0;
};

int main() {
    MeanQ88 mq;
    Mean md;

    double vals[] = {10.5, 20.25, 30.75, 15.125, 25.0, 40.0};
    for (double v : vals) {
        q8_8 qresult = mq.update(to_q8_8(static_cast<float>(v)));
        double qval = qresult / 256.0;
        double dresult = md.update(v);

        std::cout << "input=" << v
                   << " q8.8=" << qval
                   << " double=" << dresult
                   << " 誤差=" << (qval - dresult) << "\n";
    }
}
