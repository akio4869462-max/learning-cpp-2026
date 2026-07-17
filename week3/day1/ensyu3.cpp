#include <iostream>
#include <cstdint>
#include <array>
#include <vector>
#include <string>

enum class State{
    WaitCoin, WaitSelect,Dispensing
};

enum class PurchaseResult {
    Ok,
    Invalid,
    InsufficientFunds,
    OutOfStock,
};

struct Item{
    uint8_t value;
    uint8_t stock;
    std::string name;
};

class VendingMachine{
    public:
        VendingMachine(const std::vector<Item>& item) : state_(), balance_(0), item_{item} {}

        void InputCoin(uint16_t coin){
            if(state_ == State::Dispensing) return;
            
            balance_ = static_cast<uint16_t>(balance_ + coin);
            state_ = State::WaitSelect;
        }
        
        PurchaseResult SelectItem(uint8_t itemNum){
            if(state_ == State::Dispensing || itemNum >= item_.size()) return PurchaseResult::Invalid;

            if(balance_ >= item_[itemNum].value){
                if(item_[itemNum].stock > 0){
                    balance_ = static_cast<uint16_t>(balance_ - item_[itemNum].value);
                    item_[itemNum].stock--;
                    state_ = State::Dispensing;
                    if(balance_ == 0){
                        state_ = State::WaitCoin;
                    }else{
                        state_ = State::WaitSelect;
                    }
                    return PurchaseResult::Ok;
                }else{
                    std::cout << item_[itemNum].name << "は在庫切れです。" << std::endl;
                    return PurchaseResult::OutOfStock;
                }
            }else{
                std::cout << "挿入金額が足りていません。" << std::endl;
                return PurchaseResult::InsufficientFunds;
            }
        }

        uint16_t OutputCoin(){
            uint16_t out = balance_;
            balance_ = 0;
            state_ = State::WaitCoin;
            return out;
        }

    private:
        State state_;
        uint16_t balance_;
        std::vector<Item> item_{};
};

int main(){
    std::vector<Item> items = {
        {100, 10, "水"},
        {120,  0, "お茶"},
        {200,  5, "エナジードリンク"},
    };

    VendingMachine vm(items);

    std::cout << "--- シナリオ1: 正常購入 ---" << std::endl;
    vm.InputCoin(100);
    PurchaseResult r1 = vm.SelectItem(0);
    std::cout << "結果: " << static_cast<int>(r1) << " (0=Ok想定)" << std::endl;
    std::cout << "お釣り: " << vm.OutputCoin() << std::endl;

    std::cout << "--- シナリオ2: 金額不足 ---" << std::endl;
    vm.InputCoin(50);
    PurchaseResult r2 = vm.SelectItem(0);
    std::cout << "結果: " << static_cast<int>(r2) << " (2=Ok想定)" << std::endl;
    std::cout << "お釣り: " << vm.OutputCoin() << std::endl;

    std::cout << "--- シナリオ3: 在庫切れ ---" << std::endl;
    vm.InputCoin(150);
    PurchaseResult r3 = vm.SelectItem(1);
    std::cout << "結果: " << static_cast<int>(r3) << " (3=Ok想定)" << std::endl;
    std::cout << "お釣り: " << vm.OutputCoin() << std::endl;

    std::cout << "--- シナリオ4: 投入なしで返金 ---" << std::endl;
    VendingMachine vm2(items);
    uint16_t refund = vm2.OutputCoin();
    std::cout << "返金額: " << refund << " (0想定)" << std::endl;


    std::cout << "--- シナリオ5: 不正な商品番号 ---" << std::endl;
    vm.InputCoin(100);
    PurchaseResult r4 = vm.SelectItem(5);
    std::cout << "結果: " << static_cast<int>(r4) << " (1=Ok想定)" << std::endl;
    std::cout << "お釣り: " << vm.OutputCoin() << std::endl;

    return 0;
    
}