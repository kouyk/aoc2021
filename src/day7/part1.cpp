#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::vector<int> positions;
    int curr;
    while (std::cin >> curr) {
        positions.emplace_back(curr);
        std::cin.ignore();
    }
    std::ranges::nth_element(positions, positions.begin() + positions.size() / 2);
    auto median = positions[positions.size() / 2];
    unsigned long long total = 0;
    for (auto p : positions) {
        total += std::abs(p - median);
    }
    std::cout << total;
    return 0;
}
