#include <cstdint>
#include <vector>
#include <iostream>

// ボタンのチャタリング除去(10ms周期ポーリング、4回連続一致で確定)
class Debouncer {
public:
    bool update(bool raw) {               // 戻り値: 確定した押下状態
        history_ = static_cast<uint8_t>((history_ << 1) | (raw ? 1u : 0u));
        if ((history_ & 0x0Fu) == 0x0Fu) stable_ = true;
        if ((history_ & 0x0Fu) == 0x00u) stable_ = false;
        return stable_;
    }
private:
    uint8_t history_ = 0;
    bool stable_ = false;
};

int main(){
    std::vector<bool> test = {1,0,1,0,1,1,1,1,0};
    Debouncer db;
    bool result;

    for(size_t i = 0;i < test.size(); i++){
        result = db.update(test[i]);
        std::cout << result << std::endl;
    }
}