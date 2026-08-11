#include <gtest/gtest.h>
#include "OvenSystem.h"

void sendCommand(OvenSystem& sys, const std::vector<uint8_t>& payload, uint32_t tick) {
    std::vector<uint8_t> frame;
    uint8_t sum = 0;
    frame.push_back(0xAA); sum = static_cast<uint8_t>(sum + 0xAA);
    frame.push_back(static_cast<uint8_t>(payload.size()));
    sum = static_cast<uint8_t>(sum + payload.size());
    for (uint8_t b : payload) { frame.push_back(b); sum = static_cast<uint8_t>(sum + b); }
    frame.push_back(sum);
    for (uint8_t b : frame) sys.receiveByte(b, tick);
}

//test1
TEST(OvenSystem, InitTransitionsToRunningOnFirstTick) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);

    EXPECT_EQ(sys.state(), SystemState::Init);   // 最初はInit

    sys.tick(10);   // 10ms経過 → controlStepが1回実行される

    EXPECT_EQ(sys.state(), SystemState::Running);   // Runningに遷移しているはず
}

//test2
TEST(OvenSystem, RunningStaysRunningWithNormalTemperature) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);
    
    EXPECT_EQ(sys.state(), SystemState::Init);   // 最初はInit
    
    sys.tick(10);   // 10ms経過 → controlStepが1回実行される
    EXPECT_EQ(sys.state(), SystemState::Running);   // Runningに遷移しているはず
    sensor.setValue(40.0);
    sys.tick(20);   // 10ms経過 → controlStepが1回実行される
    EXPECT_EQ(sys.state(), SystemState::Running);   // Runningのままなはず
}

//test3
TEST(OvenSystem, OutOfBoundsTemperatureTriggersError) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);
    
    EXPECT_EQ(sys.state(), SystemState::Init);   // 最初はInit
    
    sys.tick(10);   // 10ms経過 → controlStepが1回実行される
    EXPECT_EQ(sys.state(), SystemState::Running);   // Runningに遷移しているはず
    sensor.setValue(110.0);
    sys.tick(20);   // 10ms経過 → controlStepが1回実行される
    EXPECT_EQ(sys.state(), SystemState::Error);   // Errorに遷移しているはず
}

//test4
TEST(OvenSystem, BelowLowerBoundTriggersError) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);
    
    EXPECT_EQ(sys.state(), SystemState::Init);   // 最初はInit
    
    sys.tick(10);   // 10ms経過 → controlStepが1回実行される
    EXPECT_EQ(sys.state(), SystemState::Running);   // Runningに遷移しているはず
    sensor.setValue(-30.0);
    sys.tick(20);   // 10ms経過 → controlStepが1回実行される
    EXPECT_EQ(sys.state(), SystemState::Error);   // Errorに遷移しているはず
}

//test5
TEST(OvenSystem, LargeDeviationTriggersError) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);
    
    EXPECT_EQ(sys.state(), SystemState::Init);   // 最初はInit
    
    sys.tick(10);
    sys.tick(20);
    sys.tick(30);
    sys.tick(40);
    sys.tick(50);
    EXPECT_EQ(sys.state(), SystemState::Running);   // Runningに遷移しているはず
    sensor.setValue(50.0);
    sys.tick(60);   // 10ms経過 → controlStepが1回実行される
    EXPECT_EQ(sys.state(), SystemState::Error);   // Errorに遷移しているはず
}

//test6
TEST(OvenSystem, ErrorRecoversToRunningAfterTimeout) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);
    
    EXPECT_EQ(sys.state(), SystemState::Init);

    sys.tick(10);
    EXPECT_EQ(sys.state(), SystemState::Running);
    sensor.setValue(110.0);
    sys.tick(20);
    EXPECT_EQ(sys.state(), SystemState::Error);
    sys.tick(1021);
    EXPECT_EQ(sys.state(), SystemState::Reset);
    sys.tick(1031);
    EXPECT_EQ(sys.state(), SystemState::Running);
}

//test7
TEST(OvenSystem, HeaterTurnsOnWhenColdBelowTarget) {
    FakeTempSensor sensor;
    sensor.setValue(20.0);
    OvenSystem sys(sensor);

    sys.tick(10);
    sys.tick(20);

    EXPECT_TRUE(sys.heaterOn());
}

//test8
TEST(OvenSystem, HeaterTurnsOffWhenHotAboveTarget) {
    FakeTempSensor sensor;
    sensor.setValue(35.0);
    OvenSystem sys(sensor);

    sys.tick(10);
    sys.tick(20);

    EXPECT_FALSE(sys.heaterOn());
}

//test9
TEST(OvenSystem, SetTargetCommandUpdatesTarget) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);

    int16_t raw_value = 355;   // 35.5度 * 10
    sendCommand(sys, {0x01, static_cast<uint8_t>((raw_value >> 8) & 0xFF), static_cast<uint8_t>(raw_value & 0xFF)}, 0);

    EXPECT_EQ(sys.target(), 35.5);
}

//test10
TEST(OvenSystem, SetTargetCommandIgnoredIfPayloadTooShort) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);

    double before = sys.target();   // 変更前の値(初期値30)を覚えておく

    sendCommand(sys, {0x01}, 0);   // コマンドIDだけで、値がない不完全なペイロード

    EXPECT_EQ(sys.target(), before);   // 変わっていないはず
}

//test11
TEST(OvenSystem, GetCurrentCommandStoresFilteredValue) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);

    sys.tick(10);   // Init → Running(filtered_が25になる)

    sendCommand(sys, {0x02}, 20);   // 現在値取得コマンド

    EXPECT_EQ(sys.lastQueriedCurrent(), 25.0);
}

//test12
TEST(OvenSystem, GetStatusCommandStoresState) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);

    sys.tick(10);   // Running状態にする

    sendCommand(sys, {0x03}, 20);   // 状態取得コマンド

    EXPECT_EQ(sys.lastQueriedStatus(), SystemState::Running);
}

//test13
TEST(OvenSystem, UnknownCommandIsIgnored) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);

    double before_target = sys.target();

    sendCommand(sys, {0xFF}, 0);   // 未知のコマンドID

    EXPECT_EQ(sys.target(), before_target);   // 何も変わらないはず
}

//test14
TEST(OvenSystem, ControlStepOnlyRunsEvery10ms) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);

    for (uint32_t ms = 0; ms < 10; ms++) {
        sys.tick(ms);
        EXPECT_EQ(sys.state(), SystemState::Init);   // 10ms未満はずっとInitのまま
    }
    sys.tick(10);
    EXPECT_EQ(sys.state(), SystemState::Running);   // 10msでようやく進む
}


//test15
TEST(OvenSystem, TickDoesNotCrashWithoutAnyBytes) {
    FakeTempSensor sensor;
    sensor.setValue(25.0);
    OvenSystem sys(sensor);

    for (uint32_t ms = 0; ms <= 2000; ms += 10) {
        sys.tick(ms);
    }
    // でたらめなバイト列を送ってみる(フレームとして不正)
    sys.receiveByte(0x00, 2001);
    sys.receiveByte(0xFF, 2002);
    sys.receiveByte(0x12, 2003);

    SUCCEED();   // ここまで到達すればクラッシュしていない、というテスト
}