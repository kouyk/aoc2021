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
        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> pq;
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
        grid.grid_max = line.length();
        grid.risk.reserve(grid.grid_max);
        grid.visited.resize(grid.grid_max, std::vector<bool>(grid.grid_max, false));

        do {
            grid.risk.emplace_back();
            grid.risk.back().reserve(grid.grid_max);
            std::ranges::transform(line, std::back_inserter(grid.risk.back()), [](auto c) { return c - '0'; });
        } while (std::getline(in, line));
        return in;
    }
};

int main() {
    Grid grid;
    std::cin >> grid;
    std::cout << grid.minrisk();
    return 0;
}
