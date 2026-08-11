#ifndef OVENSYSTEM_H
#define OVENSYSTEM_H

#include <cstdint>
#include <cmath>
#include <iostream>
#include "TempSensor.h"
#include "Filter.h"
#include "Hysteresis.h"
#include "FrameParser.h"

enum class SystemState{
    Init, Running, Error, Reset
};

class OvenSystem {
    public:
        explicit OvenSystem(ITempSensor& sensor)
            : sensor_(sensor), Hysteresis_(2.0, -2.0), parser_(&OvenSystem::onFrameStatic, this) {}   // 閾値を渡す

        void tick(uint32_t now_ms) {
            if (now_ms - last_control_ms_ >= 10) {
                last_control_ms_ = now_ms;
                controlStep(now_ms);
            }
            // TODO: 100ms周期の通信処理、1s周期のログ出力も後で同じ形で追加
            if(now_ms - last_log_ms_ >= 1000){
                last_log_ms_ = now_ms;
                logStatus(now_ms);
            }
        }

        void receiveByte(uint8_t byte, uint32_t tick) {
            parser_.feed(byte, tick);
        }
        
        void logStatus(uint32_t now_ms) {
        std::cout << now_ms << " " << static_cast<int>(state_) << " "
                    << filtered_ << " " << target_ << " " << heater_on_ << std::endl;
        }
        
        SystemState state() const { return state_; }
        bool heaterOn() const { return heater_on_; }
        double target() const { return target_; }
        double lastQueriedCurrent() const { return last_queried_current_; }
        SystemState lastQueriedStatus() const { return last_queried_status_; }
        
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
        static void onFrameStatic(const uint8_t* payload, uint8_t len, void* ctx) {
            auto* self = static_cast<OvenSystem*>(ctx);
            self->onFrame(payload, len);
        }

        void onFrame(const uint8_t* payload, uint8_t len) {
            // TODO: ここでpayload[0](コマンドID)を見て分岐する
            if(len < 1) return;
            switch (payload[0])
            {
            case 0x01:{
                /* code */
                if(len < 3) return;
                int16_t raw_value = static_cast<int16_t>((payload[1] << 8) | payload[2]);
                target_ = raw_value / 10.0;
                break;
            }
            case 0x02:   // 現在値取得
                last_queried_current_ = filtered_;
                break;
            case 0x03:   // 状態取得
                last_queried_status_ = state_;
                break;
            
            default:
                break;
            }
        }

        FrameParser parser_;
        double last_queried_current_ = 0.0;
        SystemState last_queried_status_ = SystemState::Init;
        uint32_t last_log_ms_ = 0;
};

#endif