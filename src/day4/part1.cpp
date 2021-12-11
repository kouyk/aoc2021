#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>
#include <sstream>

namespace sr = std::ranges;
namespace sv = std::views;

class Puzzle {
private:
    struct Coordinate {
        const short row, column;
        Coordinate(short r, short c) : row(r), column(c) {};
    };

    static const int NUM_ROW = 5, NUM_COLUMN = 5;

    std::unordered_map<int, Coordinate> grid;
    std::vector<int> rowMarked;
    std::vector<int> columnMarked;
    std::vector<std::vector<bool>> marked{NUM_ROW, std::vector<bool>(NUM_COLUMN, false)};

public:
    Puzzle() : rowMarked(NUM_ROW, 0), columnMarked(NUM_COLUMN, 0) {};
    void reset() {
        grid.clear();
        sr::fill(rowMarked, 0);
        sr::fill(columnMarked, 0);
        for (auto &row : marked) {
            std::fill(row.begin(), row.end(), false);
        }
    }
    bool mark(int v) {
        if (!grid.contains(v))
            return false;

        const auto &pos = grid.at(v);
        marked[pos.row][pos.column] = true;
        ++rowMarked[pos.row];
        ++columnMarked[pos.column];
        return rowMarked[pos.row] == NUM_ROW || columnMarked[pos.column] == NUM_COLUMN;
    }
    int sum() const {
        int sum = 0;
        for (const auto &pos : grid) {
            if (marked[pos.second.row][pos.second.column]) continue;

            sum += pos.first;
        }
        return sum;
    }

    friend std::istream& operator>>(std::istream &is, Puzzle &puzzle) {
        for (short r = 0; r < NUM_ROW; ++r) {
            for (short c = 0; c < NUM_COLUMN; ++c) {
                int value;
                is >> value;
                puzzle.grid.emplace(value, Coordinate{r, c});
            }
        }
        return is;
    }
};

int main() {
    std::string order;
    std::getline(std::cin, order);
    std::stringstream ss(order);
    std::vector<int> numbers;
    while (std::getline(ss, order, ',')) {
        numbers.emplace_back(std::stoi(order));
    }
    Puzzle p;
    auto num_steps = numbers.size();
    int score;
    while (std::cin >> p) {
        for (int i = 0; i < num_steps; ++i) {
            auto bingo = p.mark(numbers[i]);
            if (bingo) {
                if (i + 1 < num_steps) {
                    num_steps = i + 1;
                    score = p.sum() * numbers[i];
                }
                break;
            }
        }
        p.reset();
    }
    std::cout << score;
    return 0;
}
