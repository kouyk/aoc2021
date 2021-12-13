#include <iostream>
#include <sstream>
#include <map>
#include <ranges>
#include <algorithm>
#include <set>
#include <numeric>

class Graph {
private:
    struct Cave {
        std::set<Cave*> neighbours;
        bool small;
        bool visited = false;

        explicit Cave(const bool &b) : small(b) {}
    };

    std::map<std::string, Cave> vertex;
    Cave *twice = nullptr;

    int getNumPathToEnd(Cave *c) {
        if (c == &vertex.at("end"))
            return 1;
        if (c->visited && (twice != nullptr || c == &vertex.at("start")))
            return 0;

        if (c->small) {
            if (c->visited)
                twice = c;
            else
                c->visited = true;
        }
        auto total = std::transform_reduce(c->neighbours.begin(), c->neighbours.end(), 0, std::plus<>(),
                                           [this](auto ptr) { return getNumPathToEnd(ptr); });
        if (c == twice)
            twice = nullptr;
        else
            c->visited = false;
        return total;
    }

public:
    Graph() = default;
    void addEdge(const std::string &u, const std::string &v) {
        if (!vertex.contains(u))
            vertex.emplace(u, std::ranges::all_of(u, islower));
        if (!vertex.contains(v))
            vertex.emplace(v, std::ranges::all_of(v, islower));
        vertex.at(u).neighbours.emplace(&vertex.at(v));
        vertex.at(v).neighbours.emplace(&vertex.at(u));
    }
    int getPathCount() {
        return getNumPathToEnd(&vertex.at("start"));
    }
};

int main() {
    std::string line;
    Graph graph;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string u, v;
        std::getline(ss, u, '-');
        std::getline(ss, v);

        graph.addEdge(u, v);
    }

    std::cout << graph.getPathCount();
    return 0;
}
