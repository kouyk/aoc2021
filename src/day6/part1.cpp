#include <iostream>
#include <numeric>

const int DAYS = 80;

int main() {
    unsigned long long timers[9] = {0}, curr;
    while (std::cin >> curr) {
        ++timers[curr];
        std::cin.ignore();
    }
    for (int i = 0; i < DAYS; ++i) {
        auto birthers = timers[0];
        for (int j = 0; j < 8; ++j) {
            timers[j] = timers[j+1];
        }
        timers[6] += birthers;
        timers[8] = birthers;
    }
    std::cout << std::reduce(timers, timers + 9);
    return 0;
}
