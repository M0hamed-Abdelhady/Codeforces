#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()


const int N = 1e5 + 3, F = 1e2 + 3, mod = 1e9 + 7;

int logs[N], sparse[N][19];

void build(vector<int> &value) {
//  building sparse table (RMQ) for value
    int n = value.size() - 1;
    int lOG = __lg(n + 1) + 1;
    for (int sz = 0; sz < lOG; ++sz) {
        for (int i = 0; i + (1 << sz) - 1 <= n; ++i) {
            if (!sz)sparse[i][sz] = value[i];
            else {
                sparse[i][sz] = max(sparse[i][sz - 1], sparse[i + (1 << (sz - 1))][sz - 1]);
            }
        }
    }
}


int query(int l, int r) {
//   get max in range from l to r
    int log = logs[r - l + 1];
    return max(sparse[l][log], sparse[r - (1 << log) + 1][log]);
}


int calcCost(string &s) {
//  calculate the cost to make string palindrome
    int q = 0, l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r])++q;
        ++l, --r;
    }
    return q;
}


void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 2; i < n; ++i) {
//      reset array
        memset(sparse[i], 0, sizeof sparse[i]);
    }
    vector<string> words(n);
    vector<int> value(n + 1), cost(n + 1);

    for (int i = 0; i < n; ++i) cin >> words[i];

    for (int i = 1; i <= n; ++i) cin >> value[i];

    for (int i = 0; i < n; ++i) {
//      calculate the cost for each word
        cost[i + 1] = calcCost(words[i]);
    }

//  prefix on cost and value
    for (int i = 1; i <= n; ++i) cost[i] += cost[i - 1];
    for (int i = 1; i <= n; ++i) value[i] += value[i - 1];

//  run the function to build the sparse table
    build(value);

    int ans = INT32_MIN;
    for (int i = 0; i <= n; i++) {
//  binary search on cost (prefix of the cost) to find cost no more than k ==> cost[i + x] - cost[i] <= k
        auto f = upper_bound(cost.begin() + i + 1, cost.end(), cost[i] + k);
        --f;
//  maximize the value you of each optimal cost
        ans = max(ans, query(i, f - cost.begin()) - value[i]);
    }
    cout << ans << endl;
}


int main() {
//  preprocessing for log2(sz)
//  efficiently find x satisfy 2^x <= sz ---> x = logs[sz]
    logs[1] = 0;
    for (int i = 2; i < N; ++i) logs[i] = logs[i / 2] + 1;

    ll T;
    cin >> T;
    while (T--)solve();
    return 0;
}
