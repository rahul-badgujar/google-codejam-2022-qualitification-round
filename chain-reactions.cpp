#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

using vi = vector<int>;

class Solution {
   public:
    int n;
    vi fun;
    vi points;
    vi indegree;
    vi initiators;
    map<int, pair<int, int>> allowed;

    Solution(int _n) : n(_n) {
        init();
        preprocess();
    }

    void init() {
        fun.resize(n + 1);
        points.resize(n + 1);
        indegree.resize(n + 1, 0);
        fun[0] = 0, points[0] = -1;
        for (int i = 1; i <= n; ++i) {
            cin >> fun[i];
        }
        for (int i = 1; i <= n; ++i) {
            cin >> points[i];
            indegree[points[i]]++;
        }
    }
    void preprocess() {
        for (int i = 1; i <= n; ++i) {
            if (indegree[i] == 0) initiators.push_back(i);
        }
        for (const auto& initiator : initiators) {
            setAlloweds(initiator, initiator, fun[initiator]);
        }
    }
    int result() {
        int ans = 0;
        for (const auto& initiator : initiators) {
            ans += maxVal(initiator, initiator, fun[initiator]);
        }
        return ans;
    }

    void setAlloweds(const int& u, const int& initiator, int maxTill) {
        if (allowed.find(u) == allowed.end()) {
            allowed[u] = {maxTill, initiator};
        } else {
            auto& allowedVal = allowed[u];
            if (maxTill < allowedVal.first) {
                allowedVal = {maxTill, initiator};
            } else {
                return;
            }
        }
        maxTill = max(maxTill, fun[u]);
        int v = points[u];
        if (v != -1) {
            setAlloweds(v, initiator, maxTill);
        }
    }

    int maxVal(const int& u, const int& initiator, int maxTill) {
        const auto& allowedVal = allowed[u];
        if (allowedVal.second == initiator) {
            int v = points[u];
            if (v == -1) return maxTill;
            maxTill = max(maxTill, fun[u]);
            return maxVal(v, initiator, maxTill);
        } else {
            return maxTill;
        }
    }
};

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        int n;
        cin >> n;
        Solution sol(n);
        int ans = sol.result();
        cout << ans << endl;
    }
    return 0;
}