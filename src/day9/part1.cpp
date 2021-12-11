#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

const int MAX_RISK = 10;

int main() {
    std::vector<std::vector<int>> heightmap;
    std::vector<std::vector<bool>> visited;
    std::string line;
    while (std::getline(std::cin, line)) {
        heightmap.emplace_back(), visited.emplace_back();
        heightmap.reserve(line.length()), visited.reserve(line.length());
        std::ranges::for_each(line, [&](auto c) {
            heightmap.back().emplace_back(c - '0' + 1);
            visited.back().emplace_back(heightmap.back().back() == MAX_RISK);
        });
    }
    const auto length = heightmap.size() - 1, width = heightmap.back().size() - 1;
    auto h = [&](auto y, auto x) { return heightmap[y][x]; };
    auto v = [&](auto y, auto x) { return visited[y][x]; };
    int risk = 0;
    for (int i = 0; i <= length; ++i) {
        for (int j = 0; j <= width; ++j) {
            if (v(i, j))
                continue;

            auto basin = true;
            if (i > 0)
                if (h(i, j) >= h(i-1, j))
                    basin = false;
            if (basin && j > 0)
                if (h(i, j) >= h(i, j-1))
                    basin = false;
            if (j < width) {
                if (h(i, j) < h(i, j + 1))
                    v(i, j + 1) = true;
                else
                    basin = false;
            }
            if (i < length) {
                if (h(i, j) < h(i + 1, j))
                    v(i + 1, j) = true;
                else
                    basin = false;
            }

            if (basin)
                risk += h(i, j);

            v(i, j) = true;
        }
    }
    std::cout << risk;
    return 0;
}
