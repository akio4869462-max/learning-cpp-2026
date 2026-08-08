#include <gtest/gtest.h>
#include "ringbuf.h"

TEST(RingBuf, PushPopPreservesOrder) {
    RingBuf rb(4);
    ASSERT_TRUE(rb.push(1));
    ASSERT_TRUE(rb.push(2));
    uint8_t out = 0;
    ASSERT_TRUE(rb.pop(out));
    EXPECT_EQ(out, 1);
}

TEST(RingBuf, PushToFullFails) {
    RingBuf rb(2);
    rb.push(1);
    rb.push(2);
    EXPECT_FALSE(rb.push(3));      // 容量2なら3個目は失敗
}

TEST(RingBuf, PopFromEmptyFails) {
    RingBuf rb(2);
    uint8_t out = 0;
    EXPECT_FALSE(rb.pop(out));
}
