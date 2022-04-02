#include <iostream>
using namespace std;

char getCharToPrint(int r, bool firstActive) {
    if ((r & 1) == 0) {
        return firstActive ? '+' : '-';
    } else {
        return firstActive ? '|' : '.';
    }
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int R, C;
        cin >> R >> C;
        cout << "Case #" << t << ":\n";
        for (int r = 0; r < (2 * R + 1); ++r) {
            bool firstActive = true;
            for (int c = 0; c < (2 * C + 1); ++c) {
                if (r <= 1 and c <= 1) {
                    cout << ".";
                } else {
                    cout << getCharToPrint(r, firstActive);
                }
                firstActive ^= true;
            }
            cout << "\n";
        }
    }
    return 0;
}