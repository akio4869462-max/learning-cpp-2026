#include <gtest/gtest.h>
#include <vector>
#include "frameparser.h"

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

    std::vector<uint8_t> data = {0x10, 0x20, 0x30};   // 送りたいペイロード

    // フレームを組み立てる: SOF, LEN, PAYLOAD..., CHECKSUM
    std::vector<uint8_t> frame;
    uint8_t sum = 0;
    frame.push_back(0xAA); sum = static_cast<uint8_t>(sum + 0xAA);
    frame.push_back(static_cast<uint8_t>(data.size()));
    sum = static_cast<uint8_t>(sum + data.size());
    for (uint8_t b : data) {
        frame.push_back(b);
        sum = static_cast<uint8_t>(sum + b);
    }
    frame.push_back(sum);   // 正しいチェックサム

    // 1バイトずつfeedする(タイムアウトが起きないよう、tickは全部同じ値でOK)
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

    // TODO①: 1つ目のテストと同じ手順で、正しいチェックサムまでフレームを組み立てる
    std::vector<uint8_t> frame;
    uint8_t sum = 0;
    // ...(1つ目のテストのフレーム組み立て部分をコピーしてくる)
    frame.push_back(0xAA); sum = static_cast<uint8_t>(sum + 0xAA);
    frame.push_back(static_cast<uint8_t>(data.size()));
    sum = static_cast<uint8_t>(sum + data.size());
    for (uint8_t b : data) {
        frame.push_back(b);
        sum = static_cast<uint8_t>(sum + b);
    }
    frame.push_back(sum);   // 正しいチェックサム

    // TODO②: 組み立てたフレームの「最後の要素(チェックサム)」だけを、わざと違う値に書き換える
    // ヒント: frame.back() や frame[frame.size()-1] で最後の要素にアクセスできる
    frame.back() = 0x01;

    for (uint8_t b : frame) {
        fp.feed(b, 0);
    }

    // TODO③: コールバックは呼ばれていないはず、errors()は1のはず
    EXPECT_FALSE(capture.called);
    EXPECT_EQ(fp.errors(), 1u);
}

TEST(FrameParser, TimeoutDiscardsPartialFrame) {
    CaptureResult capture;
    FrameParser fp(testCallback, &capture);

    // フレームの途中まで送る(SOF, LENのみ)
    fp.feed(0xAA, 0);   // SOF
    fp.feed(0x02, 1);   // LEN=2(まだペイロード2バイト待ちの状態)

    // TODO: ここで大きくtickを進めて(100以上経過)、続きのバイトを送るとタイムアウトするはず
    fp.feed(0x99, 200);   // 何かしらのバイトを、last_tick_(1)から100以上進んだtickで送る → タイムアウトでWaitSofに戻るはず

    // その後、新しい正常なフレームを送って、コールバックが正しく呼ばれることを確認する
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
    frame.push_back(sum);   // 正しいチェックサム

    // 1バイトずつfeedする(タイムアウトが起きないよう、tickは全部同じ値でOK)
    for (uint8_t b : frame) {
        fp.feed(b, 0);
    }

    EXPECT_TRUE(capture.called);
    EXPECT_EQ(capture.payload, data);
    EXPECT_EQ(fp.errors(), 0u);
}
