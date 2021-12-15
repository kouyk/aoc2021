#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <queue>

class Grid {
private:
    int grid_max;
    std::vector<std::vector<int>> risk;
    std::vector<std::vector<bool>> visited;

public:
    Grid() = default;
    int minrisk() {
        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<>> pq;
        pq.emplace((grid_max - 1) * 2, 0, 0);
        while (!pq.empty()) {
            auto [subtotal, y, x] = pq.top();
            pq.pop();
            if (visited[y][x])
                continue;
            if (y == x && y == grid_max - 1)
                return subtotal;

            visited[y][x] = true;
            if (y > 0)
                pq.emplace(subtotal + risk[y-1][x] + 1, y-1, x);
            if (x > 0)
                pq.emplace(subtotal + risk[y][x-1] + 1, y, x-1);
            if (y < grid_max-1)
                pq.emplace(subtotal + risk[y+1][x] - 1, y+1, x);
            if (x < grid_max-1)
                pq.emplace(subtotal + risk[y][x+1] - 1, y, x+1);
        }
    }
    friend std::istream& operator>>(std::istream &in, Grid &grid) {
        std::string line;
        std::getline(in, line);
        int tile_length = line.length();
        grid.grid_max = tile_length * 5;
        grid.risk.reserve(grid.grid_max);
        grid.visited.resize(grid.grid_max, std::vector<bool>(grid.grid_max, false));

        do {
            grid.risk.emplace_back();
            grid.risk.back().reserve(grid.grid_max);
            std::ranges::transform(line, std::back_inserter(grid.risk.back()), [](auto c) { return c - '0'; });
        } while (std::getline(in, line));
        for (auto &row : grid.risk) {
            row.resize(grid.grid_max);
            for (int i = tile_length; i < grid.grid_max; ++i) {
                row[i] = row[i-tile_length] + 1;
                if (row[i] == 10)
                    row[i] = 1;
            }
        }
        grid.risk.resize(grid.grid_max, std::vector<int>(grid.grid_max));
        for (int i = tile_length; i < grid.grid_max; ++i)
            std::transform(grid.risk[i-tile_length].begin(), grid.risk[i-tile_length].end(),
                           grid.risk[i].begin(), [](auto j) { return ++j == 10 ? 1 : j; });
        return in;
    }
};

int main() {
    Grid grid;
    std::cin >> grid;
    std::cout << grid.minrisk();
    return 0;
}
