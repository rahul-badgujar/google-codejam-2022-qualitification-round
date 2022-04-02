#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix;

const int colorLimit = 1000000;

int minOutOf(vector<int> v) {
    int minimum = colorLimit + 1;
    for (const auto &e : v) {
        minimum = min(minimum, e);
    }
    return minimum;
}

int sumOfAll(vector<int> v) {
    int sum = 0;
    for (const auto &e : v) {
        sum += e;
    }
    return sum;
}

int main() {
    // c m y k

    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        // colors input
        matrix colors(4, vector<int>(3, 0));
        for (int j = 0; j < 3; ++j) {
            for (int i = 0; i < 4; ++i) {
                cin >> colors[i][j];
            }
        }
        // logic
        vector<int> minVals(4, 0);
        for (int i = 0; i < 4; ++i) {
            minVals[i] = minOutOf(colors[i]);
        }
        int minTotal = sumOfAll(minVals);
        if (minTotal < colorLimit) {
            cout << "IMPOSSIBLE";
        } else {
            // sort(minVals.begin(), minVals.end());
            int rem = colorLimit;
            for (const auto &e : minVals) {
                cout << min(rem, e) << ' ';
                rem -= min(rem, e);
            }
        }
        cout << '\n';
    }
    return 0;
}