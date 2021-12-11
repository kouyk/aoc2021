#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>
#include <ranges>
#include <array>
#include <map>

static const int PATTERN_EIGHT = 0b1111111;

inline int convertPattern(const std::string &pattern) {
    int temp = 0;
    for (auto c : pattern)
        temp |= 1 << (c - 'a');
    return temp;
}

int main() {
    int total = 0;
    std::string line;
    while (std::getline(std::cin, line, '|')) {
        std::stringstream ss;
        ss.str(line);
        std::array<int, 10> patterns{0};
        int one, four, seven;
        std::vector<int> l6;
        l6.reserve(3);
        for (int i = 0; i < 10; ++i) {
            std::string pattern;
            ss >> pattern;
            patterns[i] = convertPattern(pattern);
            switch (pattern.length()) {
                case 2:
                    one = i;
                    break;
                case 3:
                    seven = i;
                    break;
                case 4:
                    four = i;
                    break;
                case 6:
                    l6.emplace_back(i);
                    break;
            }
        }
        auto segment_a = patterns[one] ^ patterns[seven], segment_bd = patterns[one] ^ patterns[four];
        auto segment_cde = std::transform_reduce(l6.begin(), l6.end(),PATTERN_EIGHT,std::bit_and<>(),
                [&](int i) { return patterns[i]; }) ^ PATTERN_EIGHT;
        auto segment_d = segment_bd & segment_cde, segment_b = segment_bd ^ segment_d;
        auto segment_eg = PATTERN_EIGHT ^ patterns[four] ^ segment_a;
        auto segment_e = segment_cde & segment_eg, segment_c = segment_cde ^ (segment_d | segment_e);
        auto segment_f = patterns[one] ^ segment_c;
        // auto segment_g = segment_eg ^ segment_e;
        const std::map<int, int> digit = {
                {PATTERN_EIGHT ^ segment_d,             0},
                {patterns[one],                         1},
                {PATTERN_EIGHT ^ segment_b ^ segment_f, 2},
                {PATTERN_EIGHT ^ segment_b ^ segment_e, 3},
                {patterns[four],                        4},
                {PATTERN_EIGHT ^ segment_c ^ segment_e, 5},
                {PATTERN_EIGHT ^ segment_c,             6},
                {patterns[seven],                       7},
                {PATTERN_EIGHT,                         8},
                {PATTERN_EIGHT ^ segment_e,             9}
        };

        ss.clear();
        std::getline(std::cin, line);
        ss.str(line);
        int display = 0;
        for (int i = 0; i < 4; ++i) {
            std::string pattern;
            ss >> pattern;
            display *= 10;
            display += digit.at(convertPattern(pattern));
        }
        total += display;
    }
    std::cout << total;
    return 0;
}
