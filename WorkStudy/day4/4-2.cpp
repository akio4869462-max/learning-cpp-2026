#include<vector>
#include<iostream>

class WaveForm {
    public:
        WaveForm(std::vector<double> wf) : wf_(wf) {}
        double size() const {
            return wf_.size();
        }
        double max() const {
            double m = wf_[0];
            for (const auto& w : wf_) {
                if (w > m) m = w;
            }
            return m;
        }
    private:
        std::vector<double> wf_;
};

int main() {
    std::vector<double> v = {3.5, 1.2, 7.8, 2.1};
    WaveForm w(v);
    std::cout << "size = " << w.size() << ", max = " << w.max() << std::endl;
    return 0;
}