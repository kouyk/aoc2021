#include <iostream>
using namespace std;

int main() {
    int count = 0;
    int prev = INT32_MAX, curr;
    while (cin >> curr) {
        if (curr > prev) ++count;
        prev = curr;
    }
    cout << count << endl;
    return 0;
}
