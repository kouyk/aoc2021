#include <iostream>
#include <queue>
using namespace std;

int main() {
    int count = 0;
    queue<int> window;
    int curr;
    for (int i = 0; i < 3; ++i) {
        cin >> curr;
        window.push(curr);
    }
    while (cin >> curr) {
        window.push(curr);
        if (window.back() > window.front()) ++count;
        window.pop();
    }
    cout << count << endl;
    return 0;
}
