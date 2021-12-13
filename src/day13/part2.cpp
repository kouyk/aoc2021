#include <iostream>
#include <vector>
#include <sstream>
#include <ranges>
#include <algorithm>

class Paper {
private:
    struct Point {
        int x, y;
        Point(int x, int y) : x(x), y(y) {}
    };

    std::vector<std::vector<bool>> grid;
    std::vector<Point> dots;
    int max_x = 0, max_y = 0;

public:
    Paper() = default;
    void addDot(int x, int y) {
        dots.emplace_back(x, y);
        max_x = std::max(x, max_x);
        max_y = std::max(y, max_y);
    }
    void confirmDots() {
        ++max_x, ++max_y;
        grid.resize(max_y, std::vector<bool>(max_x, false));
        std::ranges::for_each(dots, [this](auto p) { grid[p.y][p.x] = true; });
    }
    void fold(char axis, int value) {
        if (axis == 'x') {
            for (int x = value + 1; x < max_x; ++x)
                for (int y = 0; y < max_y; ++y)
                    grid[y][value * 2 - x] = grid[y][value * 2 - x] || grid[y][x];
            max_x = value;
        }
        else {
            for (int y = value + 1; y < max_y; ++y)
                for (int x = 0; x < max_x; ++x)
                    grid[value * 2 - y][x] = grid[value * 2 - y][x] || grid[y][x];
            max_y = value;
        }
    }
    friend std::ostream& operator<<(std::ostream& out, const Paper &p) {
        for (int y = 0; y < p.max_y; ++y) {
            for (int x = 0; x < p.max_x; ++x)
                out << (p.grid[y][x] ? '#' : ' ');
            out << '\n';
        }
        return out;
    }
};

int main() {
    Paper paper;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.length() == 0)
            break;

        std::stringstream ss(line);
        int x, y;
        ss >> x;
        ss.ignore();
        ss >> y;

        paper.addDot(x, y);
    }
    paper.confirmDots();

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        ss.ignore(11); // "fold along "
        char axis;
        ss >> axis;
        ss.ignore();
        int value;
        ss >> value;

        paper.fold(axis, value);
    }

    std::cout << paper;
    return 0;
}


