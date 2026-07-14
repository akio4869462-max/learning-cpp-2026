/*
 * drill07_stl.cpp — Week2 Day4: STLコンテナ・アルゴリズム・optional
 * make drill07 && ./drill07
 */
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <algorithm>
#include <numeric>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { std::printf("  PASS  %s\n", name); } \
    else      { std::printf("  FAIL  %s\n", name); failures++; } \
} while (0)

struct Employee {
    std::string name;
    std::string dept;
    int salary;
};

/* 課題1: 指定部署の社員名一覧(元の順序を保つ)
 * ヒント: 範囲for でも std::copy_if + back_inserter でもよい */
std::vector<std::string> names_of_dept(const std::vector<Employee>& v, const std::string& dept) {
    (void)v; (void)dept;      /* TODO */
    return {};
}

/* 課題2: 給与合計
 * ヒント: std::accumulate(第4引数にラムダ) or 範囲for */
int total_salary(const std::vector<Employee>& v) {
    (void)v;                  /* TODO */
    return 0;
}

/* 課題3: 部署ごとの平均給与
 * ヒント: mapに合計と件数を貯めてから割る */
std::map<std::string, double> avg_by_dept(const std::vector<Employee>& v) {
    (void)v;                  /* TODO */
    return {};
}

/* 課題4: 最高給与の社員。空ならnullopt
 * ヒント: std::max_element + ラムダ比較 */
std::optional<Employee> top_earner(const std::vector<Employee>& v) {
    (void)v;                  /* TODO */
    return std::nullopt;
}

int main(void) {
    const std::vector<Employee> emps = {
        { "aoki",   "dev",   300 },
        { "baba",   "dev",   500 },
        { "chino",  "sales", 400 },
        { "doi",    "sales", 200 },
        { "endo",   "dev",   400 },
    };

    puts("[names_of_dept]");
    auto devs = names_of_dept(emps, "dev");
    CHECK("dev 3名・順序維持", devs.size() == 3 && devs[0] == "aoki" && devs[2] == "endo");
    CHECK("該当なしは空", names_of_dept(emps, "hr").empty());

    puts("[total_salary]");
    CHECK("合計1800", total_salary(emps) == 1800);
    CHECK("空は0", total_salary({}) == 0);

    puts("[avg_by_dept]");
    auto avg = avg_by_dept(emps);
    CHECK("dev平均400",   avg.count("dev") == 1 && avg["dev"] > 399.9 && avg["dev"] < 400.1);
    CHECK("sales平均300", avg.count("sales") == 1 && avg["sales"] > 299.9 && avg["sales"] < 300.1);

    puts("[top_earner]");
    auto top = top_earner(emps);
    CHECK("babaが最高", top.has_value() && top->name == "baba");
    CHECK("空はnullopt", !top_earner({}).has_value());

    if (failures == 0) { puts("\nALL PASS! 次: 教材 Week2 Day4 演習へ"); return 0; }
    std::printf("\n%d 件 FAIL\n", failures);
    return 1;
}
