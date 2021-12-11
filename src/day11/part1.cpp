#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <queue>

struct Point {
    int y, x;
};

class Octopus {
private:
    int energy;
    bool flashed = false;

public:
    explicit Octopus(char e) : energy(e - '0') {}
    bool increase() {
        ++energy;
        if (energy == 10){
            return flashed = true;
        }
        return false;
    }
    void reset() {
        if (flashed)
            energy = 0;
        flashed = false;
    }
    [[nodiscard]] bool hasFlashed() const {
        return flashed;
    }
};

int main() {
    std::vector<std::vector<Octopus>> grid;
    grid.reserve(10);
    std::string line;
    while (std::getline(std::cin, line)) {
        grid.emplace_back();
        grid.back().reserve(10);
        std::ranges::for_each(line, [&grid](auto &c) { grid.back().emplace_back(c); });
    }
    std::queue<Point> q;
    int flashes = 0;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < grid.size(); ++j)
            for (int k = 0; k < grid.size(); ++k)
                q.emplace(j, k);
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            if (grid[curr.y][curr.x].hasFlashed() || !grid[curr.y][curr.x].increase())
                continue;

            ++flashes;
            if (curr.y > 0) {
                if (curr.x > 0)
                    q.emplace(curr.y-1, curr.x-1);
                q.emplace(curr.y-1, curr.x);
                if (curr.x < 9)
                    q.emplace(curr.y-1, curr.x+1);
            }
            if (curr.x > 0)
                q.emplace(curr.y, curr.x-1);
            if (curr.x < 9)
                q.emplace(curr.y, curr.x+1);
            if (curr.y < 9) {
                if (curr.x > 0)
                    q.emplace(curr.y+1, curr.x-1);
                q.emplace(curr.y+1, curr.x);
                if (curr.x < 9)
                    q.emplace(curr.y+1, curr.x+1);
            }
        }
        for (int j = 0; j < grid.size(); ++j)
            for (int k = 0; k < grid.size(); ++k)
                grid[j][k].reset();
    }
    std::cout << flashes;
    return 0;
}
