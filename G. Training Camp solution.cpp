#include <bits/stdc++.h>

using namespace std;
#define ll long long


const int N = 3e5 + 5, F = 35, INF = 1e8;

int n, m, dp[N];
vector<int> problemLevel, nodeParents, adj[F];

int count(int taken, int k) {
    if (k > n)return 0;
    if (~dp[taken])return dp[taken];

    int ans = -INF;
    for (int i = 1; i <= n; ++i) {
        int mask = 1 << (i - 1);
        if (!(taken & mask) && (taken | nodeParents[i]) == taken)
            ans = max(ans, k * problemLevel[i] + count(taken | mask, k + 1));
    }
    return dp[taken] = ans;
}


void solve() {
    cin >> n >> m;
    memset(dp, -1, sizeof dp);
    problemLevel.assign(n + 3, 0);
    nodeParents.assign(n + 3, 0);
    for (int i = 0; i < n; ++i) adj[i].clear();
    cin.ignore();

    map<string, int> topics;
    for (int i = 1; i <= n; ++i) {
        string topic, difficulty;
        getline(cin, topic);
        while (topic.back() != ' ')difficulty.push_back(topic.back()), topic.pop_back();
        reverse(difficulty.begin(), difficulty.end()), topic.pop_back();
        topics[topic] = i, problemLevel[i] = stoi(difficulty);
    }
    for (int i = 0; i < m; ++i) {
        string t, a, b;
        getline(cin, t);
        auto it = t.find(" --> ");
        a = t.substr(0, it);
        b = t.substr(it + 5);
        adj[topics[a]].push_back(topics[b]);
    }

    for (int i = 1; i <= n; ++i)
        for (const auto &j: adj[i])
            nodeParents[j] |= 1 << (i - 1);

    cout << count(0, 1) << '\n';
}


int main() {
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}