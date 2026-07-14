# 穴埋めドリル — 使い方

各章を読んだら、対応するドリルを**演習の前に**やる。流れは常に:

1. ドリルのファイルを開く。`TODO` の関数だけ実装する(main のテストコードは変更しない)
2. `make drill01 && ./drill01` — **コンパイルは最初から通る**。実行すると未実装箇所が `FAIL` と表示される
3. `ALL PASS` になったら、そのドリル末尾に書いてある「次」(教材の演習)へ進む
4. メモリを扱うドリルは仕上げに `make clean && make drillXX ASAN=1` で再ビルドして検査

つまり「FAIL を1つずつ PASS に変えていく」のがドリル。答えは `../05_演習解答例.md` にほぼ同じ実装があるが、**30分詰まるまで見ない**こと。

## 対応表

| ドリル | 教材の対応箇所 | 学ぶこと |
|---|---|---|
| drill01_bits.c | Week1 Day1 | ビットセット/クリア/抽出、popcount |
| drill02_pointers.c | Week1 Day2 | ポインタ、strlen/strcmp自作、in-place反転 |
| drill03_memory.c | Week1 Day3 | malloc/realloc/free、リーク検査 |
| drill04_struct.c | Week1 Day3-4 | 構造体、qsort比較関数、関数ポインタ |
| drill05_class.cpp | Week2 Day1-2 | クラス、初期化リスト、RAII、例外 |
| drill06_polymorphism.cpp | Week2 Day3 | インターフェース、unique_ptr、仮想関数 |
| drill07_stl.cpp | Week2 Day4 | vector/map/optional、アルゴリズム+ラムダ |
| drill08_ringbuf.cpp | Week3 | テンプレート、リングバッファ(折り返し) |
| drill09_fsm.cpp | Week3 Day1 | 状態機械、未定義遷移の扱い |
| drill10_crc_debounce.cpp | Week3 Day2-3 | CRC-8(LFSR)、チャタリング除去 |

## 学習のコツ

- FAIL の**テスト名が仕様**になっている。「満杯pushはfalse」がFAILなら、その境界を見落としている
- 1つPASSにするたびに、なぜ動くようになったか一言メモ
- 全部PASSした後、`main` のテストを読み直す。「自分ならどんなテストを足すか」を考えるのがWeek3のテスト設計(GoogleTest)への布石
