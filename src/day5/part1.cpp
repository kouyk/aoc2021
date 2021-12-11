#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <sstream>

struct Point {
    int x = 0, y = 0;
    auto operator<=>(const Point&) const = default;
    friend std::istream& operator>> (std::istream &in, Point &p) {
        in >> p.x;
        in.ignore();
        in >> p.y;
        return in;
    }
};

int main() {
    std::map<Point, int> overlap;
    std::string line;
    std::stringstream ss;
    while (std::getline(std::cin, line)) {
        ss.str(line);
        Point a, b;
        ss >> a;
        ss.ignore(4);
        ss >> b;
        ss.clear();

        auto inorder = a < b;
        const auto &start = inorder ? a : b, &end = inorder ? b : a;
        if (start.x == end.x || start.y == end.y)
            for (int x = start.x; x <= end.x; ++x)
                for (int y = start.y; y <= end.y; ++y)
                    ++overlap[{x, y}];
    }

    std::cout << std::ranges::count_if(overlap, [](auto &pair) { return pair.second > 1; }) << '\n';
    return 0;
}
