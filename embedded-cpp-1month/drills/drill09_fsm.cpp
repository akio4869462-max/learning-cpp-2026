/*
 * drill09_fsm.cpp — Week3 Day1: 状態機械(オーブン制御)
 * make drill09 && ./drill09
 *
 * 遷移図(これを紙に描き写してから実装すること):
 *   Idle    --Start-->        Heating (ヒーターON)
 *   Heating --TempReached-->  Holding
 *   Heating --Fault-->        Error   (ヒーターOFF)
 *   Holding --Timeout-->      Idle    (ヒーターOFF)
 *   Holding --Fault-->        Error   (ヒーターOFF)
 *   Error   --Reset-->        Idle
 *   上記以外の(状態,イベント)組: 何もしない
 */
#include <cstdio>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { std::printf("  PASS  %s\n", name); } \
    else      { std::printf("  FAIL  %s\n", name); failures++; } \
} while (0)

enum class State { Idle, Heating, Holding, Error };
enum class Event { Start, TempReached, Timeout, Fault, Reset };

class OvenController {
public:
    /* 課題: 遷移図どおりに実装する。
     * ヒーター操作は heater_on() / heater_off() を呼ぶ */
    void handle(Event e) {
        (void)e;
        switch (state_) {
        case State::Idle:
            /* TODO */
            break;
        case State::Heating:
            /* TODO */
            break;
        case State::Holding:
            /* TODO */
            break;
        case State::Error:
            /* TODO */
            break;
        }
    }

    State state() const { return state_; }
    bool heater() const { return heater_; }

private:
    void heater_on()  { heater_ = true; }
    void heater_off() { heater_ = false; }
    State state_ = State::Idle;
    bool heater_ = false;
};

int main(void) {
    puts("[正常シーケンス: Idle->Heating->Holding->Idle]");
    OvenController c;
    CHECK("初期はIdle・ヒーターOFF", c.state() == State::Idle && !c.heater());

    c.handle(Event::Start);
    CHECK("Start -> Heating",       c.state() == State::Heating);
    CHECK("ヒーターON",             c.heater());

    c.handle(Event::TempReached);
    CHECK("TempReached -> Holding", c.state() == State::Holding);
    CHECK("ヒーターはONのまま",     c.heater());

    c.handle(Event::Timeout);
    CHECK("Timeout -> Idle",        c.state() == State::Idle);
    CHECK("ヒーターOFF",            !c.heater());

    puts("[異常系: Fault と Reset]");
    OvenController c2;
    c2.handle(Event::Start);
    c2.handle(Event::Fault);
    CHECK("Heating中のFault -> Error", c2.state() == State::Error);
    CHECK("ヒーターOFF(安全側)",       !c2.heater());
    c2.handle(Event::Reset);
    CHECK("Reset -> Idle",             c2.state() == State::Idle);

    puts("[未定義遷移は無視(ここを落とす人が多い)]");
    OvenController c3;
    c3.handle(Event::TempReached);          /* IdleでTempReached */
    CHECK("IdleでTempReached -> 変化なし", c3.state() == State::Idle);
    c3.handle(Event::Start);
    c3.handle(Event::TempReached);          /* Holdingへ */
    c3.handle(Event::Start);                /* HoldingでStart */
    CHECK("HoldingでStart -> 変化なし",    c3.state() == State::Holding);
    c3.handle(Event::Reset);                /* HoldingでReset(遷移図に無い!) */
    CHECK("HoldingでReset -> 変化なし",    c3.state() == State::Holding);

    if (failures == 0) { puts("\nALL PASS! 次: 教材 Week3 Day1 演習3(自動販売機)へ"); return 0; }
    std::printf("\n%d 件 FAIL\n", failures);
    return 1;
}
