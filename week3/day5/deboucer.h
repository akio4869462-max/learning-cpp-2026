#ifndef DEBOUCER_H
#define DEBOUCER_H

#include <cstdint>

class Deboucer {
public:
    inline bool update(bool raw) {               // 戻り値: 確定した押下状態
        history_ = static_cast<uint8_t>((history_ << 1) | (raw ? 1u : 0u));
        if ((history_ & 0x0Fu) == 0x0Fu) stable_ = true;
        if ((history_ & 0x0Fu) == 0x00u) stable_ = false;
        return stable_;
    }
private:
    uint8_t history_ = 0;
    bool stable_ = false;
};

#endif