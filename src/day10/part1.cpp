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
            {')', 3},
            {']', 57},
            {'}', 1197},
            {'>', 25137}
    };
    std::string line;
    int score = 0;
    while (getline(std::cin, line)) {
        std::stack<char> s;
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
                    if (s.top() == BRACKETS.at(b))
                        s.pop();
                    else
                        valid = false;
            }

            if (!valid) {
                score += SCORE.at(b);
                break;
            }
        }
    }
    std::cout << score;
    return 0;
}
