/*
 * drill05_class.cpp — Week2 Day1-2: クラス・コンストラクタ・RAII
 * make drill05 && ./drill05
 */
#include <cstdio>
#include <stdexcept>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { std::printf("  PASS  %s\n", name); } \
    else      { std::printf("  FAIL  %s\n", name); failures++; } \
} while (0)

/* ---- 課題1: RAIIの体感 ----
 * 「生きているインスタンス数」を数えるクラス。
 * コンストラクタで g_live を +1、デストラクタで -1 する。 */
int g_live = 0;

class Tracked {
public:
    Tracked() {
        g_live++;
    }
    ~Tracked() {
        g_live--;
    }
    Tracked(const Tracked&) = delete;             /* コピー禁止(今回は数を単純に保つため) */
    Tracked& operator=(const Tracked&) = delete;
};

/* ---- 課題2: 不変条件を守るクラス ---- */
class Account {
public:
    /* TODO: コンストラクタ: owner_ と balance_ を初期化リストで初期化。
     *       balance < 0 なら std::invalid_argument を投げる */
    explicit Account(int balance) : balance_(balance) {
        if(balance<0) throw std::invalid_argument("残高は負にできません");
    }
    
    /* TODO: amount <= 0 なら std::invalid_argument。それ以外は残高に加算 */
    void deposit(int amount) {
        if(amount<=0){
            throw std::invalid_argument("入金額は負にできません");
        }else{
            balance_ += amount;
        }
    }

    /* TODO: 残高を返すconstメンバ関数にする(constを忘れるとテストがコンパイルできない…
     *       のが本来だが、ここでは値のみ検証する) */
    int balance() const {
        return balance_;            /* 仮実装 */
    }

private:
    int balance_ = -999;
};

int main(void) {
    puts("[Tracked / RAII]");
    CHECK("初期状態 0", g_live == 0);
    {
        Tracked a;
        Tracked b;
        CHECK("スコープ内 2", g_live == 2);
    }
    CHECK("スコープを抜けたら 0(デストラクタ自動呼出)", g_live == 0);

    puts("[Account]");
    Account acc(100);
    CHECK("初期残高", acc.balance() == 100);
    acc.deposit(50);
    CHECK("入金後", acc.balance() == 150);

    bool threw = false;
    try { acc.deposit(0); } catch (const std::invalid_argument&) { threw = true; }
    CHECK("deposit(0)は例外", threw);
    CHECK("例外時に残高不変", acc.balance() == 150);

    threw = false;
    try { Account bad(-1); } catch (const std::invalid_argument&) { threw = true; }
    CHECK("負の初期残高は例外", threw);

    if (failures == 0) { puts("\nALL PASS! 次: drill06(ポリモーフィズム)へ"); return 0; }
    std::printf("\n%d 件 FAIL\n", failures);
    return 1;
}
