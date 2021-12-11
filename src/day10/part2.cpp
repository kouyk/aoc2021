#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <stack>
#include <map>


int main() {
    const std::map<char, char> BRACKETS = {
            {')', '('},
            {']', '['},
            {'}', '{'},
            {'>', '<'}
    };
    const std::map<char, int> SCORE = {
            {'(', 1},
            {'[', 2},
            {'{', 3},
            {'<', 4}
    };
    std::string line;
    std::vector<unsigned long long> scores;
    while (getline(std::cin, line)) {
        unsigned long long score = 0;
        std::stack<char> s;
        auto corrupted = false;
        for (auto b : line) {
            auto valid = true;
            switch (b) {
                case '(':
                case '[':
                case '{':
                case '<':
                    s.push(b);
                    break;
                default:
                    if (s.top() == BRACKETS.at(b)) {
                        s.pop();
                    }
                    else {
                        valid = false;
                        corrupted = true;
                    }
            }

            if (!valid) {
                break;
            }
        }
        if (!corrupted) {
            while (!s.empty()) {
                score *= 5;
                score += SCORE.at(s.top());
                s.pop();
            }
            scores.emplace_back(score);
        }
    }
    std::ranges::nth_element(scores, scores.begin() + scores.size() / 2);
    std::cout << scores[scores.size() / 2];
    return 0;
}
