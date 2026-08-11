#include <gtest/gtest.h>
#include <vector>
#include "FrameParser.h"

// コールバックが呼ばれたかどうかを外から観測するための入れ物
struct CaptureResult {
    bool called = false;
    std::vector<uint8_t> payload;
};

// FrameParserから呼ばれるコールバック。ctx経由でCaptureResultに書き込む
void testCallback(const uint8_t* payload, uint8_t len, void* ctx) {
    auto* result = static_cast<CaptureResult*>(ctx);
    result->called = true;
    result->payload.assign(payload, payload + len);
}

TEST(FrameParser, ValidFrameCallsCallback) {
    CaptureResult capture;
    FrameParser fp(testCallback, &capture);

    std::vector<uint8_t> data = {0x10, 0x20, 0x30};

    std::vector<uint8_t> frame;
    uint8_t sum = 0;
    frame.push_back(0xAA); sum = static_cast<uint8_t>(sum + 0xAA);
    frame.push_back(static_cast<uint8_t>(data.size()));
    sum = static_cast<uint8_t>(sum + data.size());
    for (uint8_t b : data) {
        frame.push_back(b);
        sum = static_cast<uint8_t>(sum + b);
    }
    frame.push_back(sum);

    for (uint8_t b : frame) {
        fp.feed(b, 0);
    }

    EXPECT_TRUE(capture.called);
    EXPECT_EQ(capture.payload, data);
    EXPECT_EQ(fp.errors(), 0u);
}

TEST(FrameParser, WrongChecksumIncrementsErrors) {
    CaptureResult capture;
    FrameParser fp(testCallback, &capture);

    std::vector<uint8_t> data = {0x10, 0x20, 0x30};

    std::vector<uint8_t> frame;
    uint8_t sum = 0;
    frame.push_back(0xAA); sum = static_cast<uint8_t>(sum + 0xAA);
    frame.push_back(static_cast<uint8_t>(data.size()));
    sum = static_cast<uint8_t>(sum + data.size());
    for (uint8_t b : data) {
        frame.push_back(b);
        sum = static_cast<uint8_t>(sum + b);
    }
    frame.push_back(sum);

    frame.back() = 0x01;

    for (uint8_t b : frame) {
        fp.feed(b, 0);
    }

    EXPECT_FALSE(capture.called);
    EXPECT_EQ(fp.errors(), 1u);
}

TEST(FrameParser, TimeoutDiscardsPartialFrame) {
    CaptureResult capture;
    FrameParser fp(testCallback, &capture);

    fp.feed(0xAA, 0);
    fp.feed(0x02, 1);

    fp.feed(0x99, 200);

    std::vector<uint8_t> data = {0x10, 0x20, 0x30};
    std::vector<uint8_t> frame;
    uint8_t sum = 0;
    frame.push_back(0xAA); sum = static_cast<uint8_t>(sum + 0xAA);
    frame.push_back(static_cast<uint8_t>(data.size()));
    sum = static_cast<uint8_t>(sum + data.size());
    for (uint8_t b : data) {
        frame.push_back(b);
        sum = static_cast<uint8_t>(sum + b);
    }
    frame.push_back(sum);

    for (uint8_t b : frame) {
        fp.feed(b, 0);
    }

    EXPECT_TRUE(capture.called);
    EXPECT_EQ(capture.payload, data);
    EXPECT_EQ(fp.errors(), 0u);
}

TEST(FrameParser, ZeroLengthFrameCallsCallback){
    CaptureResult capture;
    FrameParser fp(testCallback, &capture);

    uint8_t sum = 0xAA;
    fp.feed(0xAA, 0);
    fp.feed(0x00, 1);
    fp.feed(sum, 2);

    EXPECT_TRUE(capture.called);
    EXPECT_EQ(fp.errors(), 0u);
}
