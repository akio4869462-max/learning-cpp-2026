#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdio>

class FileHandle {
public:
    explicit FileHandle(const char* path) : fp_(std::fopen(path, "r")) {
        if (!fp_) throw std::runtime_error("open failed");
        std::cout << "file open" << std::endl;
    }
    ~FileHandle() {
        if (fp_){
            std::fclose(fp_);
            std::cout << "file close" << std::endl;
        }
    }   // デストラクタが必ず走る=閉じ忘れが構造的に不可能

    FileHandle(const FileHandle&) = delete;             // コピー禁止(所有権は1つ)
    FileHandle& operator=(const FileHandle&) = delete;

    std::FILE* get() const { return fp_; }
private:
    std::FILE* fp_;
};

void process() {
    FileHandle f("data.txt");
    // 例外が飛んでも、途中returnしても、fcloseは必ず呼ばれる
}

int main(){
    // std::cout << "---正常系テスト---" << std::endl;
    // process();  // (a) 正常系

    // std::cout << "---例外(ファイルなし)テスト---" << std::endl;
    // try {
    //     FileHandle bad("nonexistent.txt");   // (b) 存在しないファイル
    // } catch (const std::exception& e) {
    //     std::cout << "例外キャッチ: " << e.what() << std::endl;
    // }

    // std::cout << "---例外(途中で例外割込み)テスト---" << std::endl;
    // try {
    //     FileHandle f("data.txt");
    //     throw std::runtime_error("わざとエラー");   // (c) スコープ途中で別の例外
    // } catch (const std::exception& e) {
    //     std::cout << "例外キャッチ: " << e.what() << std::endl;
    // }

    FileHandle f1("data.txt");
    FileHandle f2 = f1;   // コピーしようとする

    return 0;
}
