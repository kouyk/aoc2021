#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <vector>

enum Direction { NONE, SELF, UP, DOWN, LEFT, RIGHT };

struct Coordinate {
    int y, x;

    auto operator<=>(const Coordinate&) const = default;
    [[nodiscard]] auto up() const {
        return Coordinate{y-1, x};
    }
    [[nodiscard]] auto down() const {
        return Coordinate{y+1, x};
    }
    [[nodiscard]] auto left() const {
        return Coordinate{y, x-1};
    }
    [[nodiscard]] auto right() const {
        return Coordinate{y, x+1};
    }
    [[nodiscard]] auto to(const Direction &dir) const {
        auto ret = *this;
        switch (dir) {
            case SELF:
                break;
            case UP:
                ret = up();
                break;
            case DOWN:
                ret = down();
                break;
            case LEFT:
                ret = left();
                break;
            case RIGHT:
                ret = right();
                break;
        }

        return ret;
    }
};

class HeightMap {
    const static int MAX_HEIGHT = 9;

private:
    struct Node {
        const int height;
        Direction direction = NONE;
        Coordinate basin{};
        bool visited = false;
        bool isBasin = false;

        explicit Node(char h) : height(h - '0') {}
    };

    const size_t LENGTH, WIDTH;
    std::vector<std::vector<Node>> map;
    std::map<Coordinate, int> basins;

    inline void addRow(const std::string &row) {
        map.emplace_back();
        auto &lastRow = map.back();
        lastRow.reserve(WIDTH);
        std::ranges::for_each(row, [&lastRow](auto d) { lastRow.emplace_back(d); });
    }

    Node& at(const Coordinate &c) {
        return map[c.y][c.x];
    }

    [[nodiscard]] const Node& at(const Coordinate &c) const {
        return map.at(c.y).at(c.x);
    }

    void updatePoint(const Coordinate &c) {
        auto &point = at(c);
        int lowest = point.height;
        Direction dir = SELF;
        auto isBasin = true;

        // check up
        if (c.y > 0) {
            const auto &up = at(c.up());
            if (point.height >= up.height) {
                isBasin = false;
                if (up.height < lowest) {
                    lowest = up.height;
                    dir = UP;
                }
            }
        }
        // check down
        if (c.y < LENGTH) {
            const auto &down = at(c.down());
            if (point.height >= down.height) {
                isBasin = false;
                if (down.height < lowest) {
                    lowest = down.height;
                    dir = DOWN;
                }
            }
        }
        // check left
        if (c.x > 0) {
            const auto &left = at(c.left());
            if (point.height >= left.height) {
                isBasin = false;
                if (left.height < lowest) {
                    lowest = left.height;
                    dir = LEFT;
                }
            }
        }
        // check right
        if (c.x < WIDTH) {
            const auto &right = at(c.right());
            if (point.height >= right.height) {
                isBasin = false;
                if (right.height < lowest) {
                    lowest = right.height;
                    dir = RIGHT;
                }
            }
        }

        point.direction = dir;
        point.isBasin = isBasin;
    }

    void addNeighbours(std::queue<Coordinate> &q, const Coordinate &c) const {
        // add up
        if (c.y > 0)
            add(q, c.up());
        // add down
        if (c.y < LENGTH)
            add(q, c.down());
        // add left
        if (c.x > 0)
            add(q, c.left());
        // add right
        if (c.x < WIDTH)
            add(q, c.right());
    }

    void add(std::queue<Coordinate> &q, const Coordinate &c) const {
        const auto neighbour = at(c);
        if (!neighbour.visited && neighbour.height != MAX_HEIGHT)
            q.push(c);
    }

public:
    explicit HeightMap(const std::vector<std::string> &rows) : LENGTH(rows.size() - 1), WIDTH(rows.front().size() - 1) {
        map.reserve(LENGTH);
        std::ranges::for_each(rows, [this](auto &r) { addRow(r); });
    };

    void locateBasins() {
        for (int i = 0; i <= LENGTH; ++i) {
            for (int j = 0; j <= WIDTH; ++j) {
                const Coordinate coordinate{i, j};
                auto &node = at(coordinate);
                if (node.height == MAX_HEIGHT)
                    continue;

                updatePoint(coordinate);
                if (node.isBasin) {
                    basins.emplace(coordinate, 1);
                    node.visited = true;
                    node.basin = coordinate;
                }
            }
        }
    }

    void calculateBasinSize() {
        std::queue<Coordinate> q;
        for (const auto &[c, val] : basins) {
            addNeighbours(q, c);
            while (!q.empty()) {
                auto curr = q.front();
                q.pop();

                auto &node = at(curr);
                if (node.visited)
                    continue;

                // determine basin location and increment the counter
                auto to = curr.to(node.direction);
                const auto &next = at(to);
                if (!next.visited) {
                    q.push(curr);
                    continue;
                }
                node.basin = next.basin;
                ++basins.at(node.basin);
                addNeighbours(q, curr);
                node.visited = true;
            }
        }
    }

    [[nodiscard]] int top3() const {
        std::vector<int> sizes;
        sizes.reserve(basins.size());
        std::ranges::transform(basins, std::back_inserter(sizes), [](const auto &p) { return p.second; });
        std::ranges::nth_element(sizes, sizes.begin() + 3, std::greater<>());
        return std::reduce(sizes.begin(), sizes.begin() + 3, 1, std::multiplies<>());
    }
};

int main() {
    // read in input
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(std::cin, line))
        lines.emplace_back(line);

    HeightMap heightmap(lines);
    heightmap.locateBasins();
    heightmap.calculateBasinSize();
    std::cout << heightmap.top3();
    return 0;
}
