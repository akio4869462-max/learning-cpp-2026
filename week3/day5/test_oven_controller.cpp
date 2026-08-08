#include <gtest/gtest.h>
#include "oven_controller.h"

TEST(OvenController, HeatsWhenBelowTarget) {
    FakeTempSensor sensor;
    sensor.setValue(30.0);          // 実機なしで「温度30度」を自由に注入できる
    OvenController oven(sensor);
    EXPECT_TRUE(oven.shouldHeat());
}

TEST(OvenController, StopsWhenAboveTarget) {
    FakeTempSensor sensor;
    sensor.setValue(60.0);          // 「温度60度」を注入
    OvenController oven(sensor);
    EXPECT_FALSE(oven.shouldHeat());
}

TEST(OvenController, BoundaryAtExactlyTarget) {
    FakeTempSensor sensor;
    sensor.setValue(50.0);          // 境界値ちょうど
    OvenController oven(sensor);
    EXPECT_FALSE(oven.shouldHeat());  // 50.0は「50.0未満」ではないのでfalse
}
