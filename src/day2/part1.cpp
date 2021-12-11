#include <iostream>
using namespace std;

int main() {
    string command;
    int amount, depth = 0, horizontal = 0;
    while (cin >> command >> amount) {
        if (command == "forward") {
            horizontal += amount;
        } else if (command == "down") {
            depth += amount;
        } else if (command == "up") {
            depth -= amount;
        }
    }
    cout << depth * horizontal << endl;
    return 0;
}
