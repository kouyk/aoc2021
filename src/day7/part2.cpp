#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

int distance(int pos, int dst) {
    auto dist = std::abs(pos - dst);
    return (dist * dist + dist) / 2;
}

int fuel_cost(const std::vector<int> &positions, int dst) {
    return std::transform_reduce(positions.begin(), positions.end(), 0,
                                 std::plus<>(), [&dst](auto p) { return distance(p, dst); });
}

int main() {
    std::vector<int> positions;
    int curr;
    while (std::cin >> curr) {
        positions.emplace_back(curr);
        std::cin.ignore();
    }
    auto sum = std::reduce(positions.begin(), positions.end());
    auto mean = sum / (double) positions.size();
    int lower = std::floor(mean), upper = std::ceil(mean);
    auto fuel_lower = fuel_cost(positions, lower);
    auto fuel_upper = fuel_cost(positions, upper);
    std::cout << std::min(fuel_lower, fuel_upper);
    return 0;
}
