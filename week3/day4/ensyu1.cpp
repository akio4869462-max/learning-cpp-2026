#include <array>
#include <cstddef>
#include <algorithm>

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

class Filter{
    public:
        double update(double value) {
            for(size_t i=num_;i>0;i--){
                if(i < 5) buf_[i] = buf_[i-1];
            }
            buf_[0] = value;
            if(num_<5) num_++;
            std::array<double, 5> sorted = buf_;
            std::sort(sorted.begin(), sorted.begin() + num_);
            double median = sorted[num_ / 2];
            return median;
        }
    private:
        std::array<double, 5> buf_{};
        size_t num_ = 0;
};

class Hysteresis{
    public:
        Hysteresis(double on_threshold, double off_threshold)
        : on_threshold_(on_threshold), off_threshold_(off_threshold) {}

        bool update(double value){
            if(!on_ && value > on_threshold_) on_ = true;
            else if(on_ && value < off_threshold_) on_ = false;
            return on_;
        }
    private:
        bool on_ = false;
        double on_threshold_, off_threshold_;
};

#include <fstream>
#include <random>

int main() {
    Mean mean;
    Filter filter;
    std::ofstream csv("output.csv");
    csv << "index,raw,mean,median\n";

    std::mt19937 rng(42);                              // 再現性のため固定シード
    std::normal_distribution<double> noise(0.0, 1.0);   // 平均0、標準偏差1のノイズ

    for (int i = 0; i < 50; i++) {
        double raw = 20.0 + noise(rng);   // 基準値20にノイズを乗せる
        if (i == 10 || i == 30) raw = 100.0;   // 時々スパイクを混ぜる

        double m = mean.update(raw);
        double med = filter.update(raw);

        csv << i << "," << raw << "," << m << "," << med << "\n";
    }
}
