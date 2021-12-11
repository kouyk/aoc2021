#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>

namespace rs = std::ranges;
namespace rv = std::views;

int main() {
    std::string line;
    std::getline(std::cin, line);
    auto bits = line.length();
    int total = 0;
    std::vector<int> ones(bits, 0);
    do {
        ++total;
        for (int i = 0; i < bits; ++i)
            if (line[i] == '1')
                ++ones[i];
    } while (std::getline(std::cin, line));
    int gamma = 0, epsilon = 0;
    for (int i = 0; i < bits; ++i) {
        if (ones[i] * 2 > total)
            gamma |= 1 << (bits - 1 - i);
        else
            epsilon |= 1 << (bits - 1 - i);
    }
    std::cout << gamma * epsilon;
    return 0;
}
