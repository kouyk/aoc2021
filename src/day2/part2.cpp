#include <iostream>
using namespace std;

int main() {
    string command;
    int amount, depth = 0, horizontal = 0, aim = 0;
    while (cin >> command >> amount) {
        if (command == "forward") {
            horizontal += amount;
            depth += aim * amount;
        } else if (command == "down") {
            aim += amount;
        } else if (command == "up") {
            aim -= amount;
        }
    }
    cout << depth * horizontal << endl;
    return 0;
}
