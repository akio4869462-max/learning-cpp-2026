/*
 * drill06_polymorphism.cpp — Week2 Day3: インターフェース・unique_ptr・仮想関数
 * make drill06 && ./drill06
 */
#include <cstdio>
#include <cstdint>
#include <memory>
#include <vector>
#include <string_view>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { std::printf("  PASS  %s\n", name); } \
    else      { std::printf("  FAIL  %s\n", name); failures++; } \
} while (0)

/* ドライバのインターフェース(実装済み)
 * 基底のデストラクタが virtual である理由を説明できるか? */
struct IDriver {
    virtual ~IDriver() = default;
    virtual void write(uint8_t byte) = 0;
    virtual const char* name() const = 0;
};

/* 課題1: 書き込みを記録するモック実装。
 * IDriverを継承し、writeで received に追記、nameは "mock" を返す。
 * override キーワードを必ず付けること */
class MockDriver : public IDriver {
public:
    std::vector<uint8_t> received;

    void write(uint8_t byte) override {
        received.push_back(byte);
    }
    const char* name() const override {
        return "mock";
    }
};

/* 課題2: MockDriverをヒープに作ってunique_ptrで返す
 * ヒント: std::make_unique。newは直接書かない */
std::unique_ptr<MockDriver> make_mock() {
    return std::make_unique<MockDriver>();
}

/* 課題3: 全ドライバに同じバイト列を書き込む
 * IDriver のポインタ経由で仮想関数が解決される(ポリモーフィズム) */
void write_all(std::vector<std::unique_ptr<IDriver>>& drivers,
               const std::vector<uint8_t>& bytes) {
    (void)drivers; (void)bytes;   /* TODO */
    for(auto& driver : drivers){
        for(uint8_t byte : bytes){
            driver->write(byte);
        }
    }
}

int main(void) {
    puts("[make_mock]");
    auto mock = make_mock();
    CHECK("nullptrでない", mock != nullptr);
    if (!mock) { std::printf("\nmake_mock()未実装のため以降スキップ\n"); return 1; }

    puts("[MockDriver]");
    mock->write(0x55);
    mock->write(0xAA);
    CHECK("記録される", mock->received.size() == 2 &&
                        mock->received[0] == 0x55 && mock->received[1] == 0xAA);
    CHECK("name", std::string_view(mock->name()) == "mock");

    puts("[write_all(ポリモーフィズム)]");
    std::vector<std::unique_ptr<IDriver>> drivers;
    auto m1 = make_mock();
    auto m2 = make_mock();
    MockDriver* p1 = m1.get();    /* 所有権はvectorに移すが観察用に生ポインタを借りる */
    MockDriver* p2 = m2.get();
    drivers.push_back(std::move(m1));
    drivers.push_back(std::move(m2));

    write_all(drivers, {1, 2, 3});
    CHECK("全ドライバに3バイト", p1->received.size() == 3 && p2->received.size() == 3);
    CHECK("順序が保たれる", p1->received[0] == 1 && p1->received[2] == 3);

    /* drivers がスコープを抜けるとき unique_ptr が自動 delete する。
     * ~IDriver が virtual でなかったら何が起きるか、教材 Week2 Day3 演習2で確認 */
    if (failures == 0) { puts("\nALL PASS! 次: drill07(STL)へ"); return 0; }
    std::printf("\n%d 件 FAIL\n", failures);
    return 1;
}
