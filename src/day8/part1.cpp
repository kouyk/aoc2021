#include <iostream>

int main() {
    std::string curr;
    int total = 0;
    while (std::cin >> curr) {
        for (int i = 0; i < 9; ++i)
            std::cin >> curr;
        // delimiter
        std::cin >> curr;
        for (int i = 0; i < 4; ++i) {
            std::cin >> curr;
            auto length = curr.length();
            if (length == 2 || length == 3 || length == 4 || length == 7)
                ++total;
        }
    }
    std::cout << total;
    return 0;
}
