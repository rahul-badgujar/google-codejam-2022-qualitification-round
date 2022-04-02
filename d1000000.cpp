#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        // input
        int n;
        cin >> n;
        vector<int> s(n);
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
        }
        // preprocess
        sort(s.begin(), s.end());
        reverse(s.begin(), s.end());
        // logic
        int straightEnd = s[0];
        int currLen = 1;
        int ans = 0;
        for (int i = 1; i < n; ++i) {
            const int &e = s[i];
            int req = straightEnd - currLen;
            if (req <= 0) {
                currLen = 1;
                straightEnd = e;
            } else if (e >= req) {
                currLen++;
            } else {
                int tempStraightEnd = e + currLen;
                if (straightEnd >= tempStraightEnd) {
                    currLen++;
                    straightEnd = tempStraightEnd;
                } else {
                    currLen = 1;
                    straightEnd = e;
                }
            }
            ans = max(ans, currLen);
        }
        ans = max(ans, currLen);
        cout << ans << endl;
    }
    return 0;
}