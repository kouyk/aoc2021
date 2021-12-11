#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>

namespace sr = std::ranges;
namespace sv = std::views;


int getBitValue(int n, int pos) {
    return n >> pos & 1;
}

int main() {
    std::string line;
    std::vector<int> readings;
    std::getline(std::cin, line);
    auto length = line.length();
    do {
        readings.emplace_back(std::stoi(line, nullptr, 2));
    } while (std::getline(std::cin, line));
    auto oxygen = readings;
    auto &co2 = readings;
    for (auto pos : sv::iota(0u, length) | sv::reverse) {
        if (oxygen.size() == 1) break;
        auto one_count = sr::count_if(oxygen, [&pos](auto n) { return getBitValue(n, pos); });
        int to_erase = one_count * 2 < oxygen.size();
        std::erase_if(oxygen, [&pos, to_erase](auto n) { return getBitValue(n, pos) == to_erase; });
    }
    for (auto pos : sv::iota(0u, length) | sv::reverse) {
        if (co2.size() == 1) break;
        auto one_count = sr::count_if(co2, [&pos](auto n) { return getBitValue(n, pos); });
        int to_erase = one_count * 2 >= co2.size();
        std::erase_if(co2, [&pos, to_erase](auto n) { return getBitValue(n, pos) == to_erase; });
    }
    std::cout << oxygen[0] * co2[0];
    return 0;
}
