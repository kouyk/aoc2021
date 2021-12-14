#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <ranges>
#include <set>

typedef std::pair<char, char> rule_pair;

const int STEPS = 10;

int main() {
    std::string initial;
    std::getline(std::cin, initial);

    std::set<char> letters(initial.begin(), initial.end());

    std::map<rule_pair, long long> pair_counter;
    for (int i = 1; i < initial.length(); ++i) {
        const auto [it, insert] = pair_counter.try_emplace(std::make_pair(initial[i-1], initial[i]), 0);
        ++it->second;
    }
    std::cin.ignore();
    std::map<rule_pair, char> rules;
    std::string line;
    while (std::getline(std::cin, line)) {
        const auto pair = std::make_pair(line[0], line[1]);
        pair_counter.try_emplace(pair, 0);
        rules.emplace(pair, line.back());
        letters.insert(line[0]);
        letters.insert(line[1]);
        letters.insert(line.back());
    }

    std::map<char, long long> letter_counter;
    std::ranges::transform(letters, std::inserter(letter_counter, letter_counter.end()),
                           [](auto c) { return std::make_pair(c, 0); });
    std::ranges::for_each(initial, [&letter_counter](auto c) { ++letter_counter.at(c); });
    for (auto i : std::views::iota(0, STEPS)) {
        std::map<rule_pair, long long> created_pairs;
        for (const auto &[pair, inserted] : rules) {
            created_pairs[pair] -= pair_counter.at(pair);
            created_pairs[std::make_pair(pair.first, inserted)] += pair_counter.at(pair);
            created_pairs[std::make_pair(inserted, pair.second)] += pair_counter.at(pair);
            letter_counter.at(inserted) += pair_counter.at(pair);
        }
        std::ranges::for_each(created_pairs, [&pair_counter](const auto &p) { pair_counter.at(p.first) += p.second; });
    }
    const auto [min, max] = std::ranges::minmax(std::views::values(letter_counter));
    std::cout << max - min;
    return 0;
}