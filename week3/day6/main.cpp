#include <cstdint>
#include <cmath>
#include "TempSensor.h"
#include "Filter.h"
#include "Hysteresis.h"

enum class SystemState{
    Init, Running, Error, Reset
};

class OvenSystem {
    public:
        explicit OvenSystem(ITempSensor& sensor)
            : sensor_(sensor), Hysteresis_(2.0, -2.0) {}   // 閾値を渡す

        void tick(uint32_t now_ms) {
            if (now_ms - last_control_ms_ >= 10) {
                last_control_ms_ = now_ms;
                controlStep(now_ms);
            }
            // TODO: 100ms周期の通信処理、1s周期のログ出力も後で同じ形で追加
        }
        
        SystemState state() const { return state_; }
        bool heaterOn() const { return heater_on_; }
        
    private:
        SystemState state_ = SystemState::Init;
        ITempSensor& sensor_;
        Filter filter_;
        Hysteresis Hysteresis_;
        double raw_ = 0.0, filtered_ = 0.0;
        double lower_bound_ = -20, upper_bound_ = 100, deviation_threshold_ = 10;
        uint32_t error_entered_ms_ = 0;
        double target_ = 30.0;
        bool heater_on_ = false;
        uint32_t last_control_ms_ = 0;
        void controlStep(uint32_t now_ms) {
            switch (state_) {
                // 今のtickの中身をそのままここに移動
                case SystemState::Init:
                    /* code */
                    raw_ = sensor_.read();
                    filtered_ = filter_.update(raw_);
                    state_ = SystemState::Running;
                    break;
                case SystemState::Running:{
                    /* code */
                    raw_ = sensor_.read();
                    filtered_ = filter_.update(raw_);
                    if(filtered_ < lower_bound_ || filtered_ > upper_bound_){
                        state_ = SystemState::Error;
                        error_entered_ms_ = now_ms;
                    } else if(std::abs(raw_ - filtered_) > deviation_threshold_){
                        state_ = SystemState::Error;
                        error_entered_ms_ = now_ms;
                    }
                    double error = target_ - filtered_;
                    heater_on_ = Hysteresis_.update(error);
                    break;
                }
                case SystemState::Error:
                    /* code */
                    if(now_ms - error_entered_ms_ >= 1000){
                        state_ = SystemState::Reset;
                    }
                    break;
                case SystemState::Reset:
                    /* code */
                    state_ = SystemState::Running;
                    break;
                
                default:
                    break;
            }
        }
};