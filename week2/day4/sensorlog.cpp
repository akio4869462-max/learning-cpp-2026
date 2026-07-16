#include <iostream>
#include <climits>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Status
{
    int min = INT_MAX;
    int max = INT_MIN;
    int sum = 0;
    int count = 0;
    int anomaly_count = 0;
};

std::optional<Status> get_stats(const std::unordered_map<int, Status>& m, int id) {
    auto it = m.find(id);
    if (it == m.end()) {
        return std::nullopt;
    }
    return it->second;
}


int main(){
    std::cout << std::fixed << std::setprecision(2);   // これ以降の出力を全部「小数点以下2桁」に固定
    std::fstream file("data.csv");
    if(!file){
        std::cerr << "ファイルを開けませんでした" << std::endl;
        return 1;
    }

    std::string line;
    std::unordered_map<int, Status> stats;
    while (std::getline(file, line)){
        std::istringstream iss(line);
        int ts, id, value;
        char comma;
        if (!(iss >> ts >> comma >> id >> comma >> value)) {
            std::cerr << "不正な行: " << line << std::endl;
            continue;
        }
        // ループの中で:
        Status& s = stats[id];
        if (value == -999) {
            s.anomaly_count++;
        } else {
            if (value < s.min) s.min = value;
            if (value > s.max) s.max = value;
            s.sum += value;
            s.count++;
        }
    }


    std::vector<std::pair<int, Status>> sorted_stats(stats.begin(), stats.end());

    std::sort(sorted_stats.begin(), sorted_stats.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;   // idで昇順
    });

    for (const auto& [id, s] : sorted_stats) {
        if (s.count == 0) continue;
        std::cout << "id: " << id
                << ", min: " << s.min
                << ", max: " << s.max
                << ", ave: " << (float)s.sum / (float)s.count
                << ", anomaly: " << s.anomaly_count
                << std::endl;
    }

    auto result = get_stats(stats, 1);   // 存在するID
    if (result.has_value()) {
        std::cout << "id1のmin: " << result->min << std::endl;
    } else {
        std::cout << "見つかりません" << std::endl;
    }

    auto result2 = get_stats(stats, 999);   // 存在しないID(data.csvには無いはず)
    if (result2.has_value()) {
        std::cout << "見つかった(想定外)" << std::endl;
    } else {
        std::cout << "id999は見つかりません" << std::endl;
    }

    return 0;
}
