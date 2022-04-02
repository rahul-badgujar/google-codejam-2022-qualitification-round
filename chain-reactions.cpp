#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#define FLIMIT 1000000000
#define test 1
#define int long long int
using namespace std;

using vi = vector<int>;

class Solution {
   public:
    class Gate {
       public:
        int minMaxTill;
        int initiator;
        Gate() : Gate(FLIMIT + 1, -1) {}
        Gate(int _minMaxTill, int _initiator) : minMaxTill(_minMaxTill), initiator(_initiator) {}
        friend bool operator<(const Gate& g1, const Gate& g2) {
            return g1.minMaxTill < g2.minMaxTill;
        }
    };

    int n;
    vi fun;
    vi points;
    vi indegree;
    vi initiators;
    vector<Gate> gates;

    Solution(int _n) : n(_n) {
        init();
        preprocess();
    }

    void init() {
        fun.resize(n + 1);
        points.resize(n + 1);
        indegree.resize(n + 1, 0);
        gates.resize(n + 1, Gate());
        // fun[0] = 0, points[0] = -1;
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
        if (u < 1) return;
        Gate newGateForU = Gate(maxTill, initiator);
        auto& existingGateOfU = gates[u];
        if (newGateForU < existingGateOfU) {
            existingGateOfU = newGateForU;
            maxTill = max(maxTill, fun[u]);
            int v = points[u];
            setAlloweds(v, initiator, maxTill);
        }
    }

    int maxVal(const int& u, const int& initiator, int maxTill) {
        if (u < 1) return maxTill;
        const auto& gateOfU = gates[u];
        if (gateOfU.initiator == initiator) {
            int v = points[u];
            maxTill = max(maxTill, fun[u]);
            return maxVal(v, initiator, maxTill);
        }
        return maxTill;
    }
};

int32_t main() {
    if (test) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
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