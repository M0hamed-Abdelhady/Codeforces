#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()


const int N = 2e2 + 3, F = 1e5 + 1, mod = 1e9 + 7;
ll dp[101][F], n, w;
vector<pair<ll, ll>> items(N);


ll knapsack(ll i, ll value) {
    if (i == n || value == 0)return value ? INT_MAX : 0;
    if (dp[i][value])return dp[i][value];
    ll ans = 0;
    if (items[i].second <= value)
//      get minimum wight for the aim value
        ans = min(knapsack(i + 1, value - items[i].second) + items[i].first, knapsack(i + 1, value));
    else ans = knapsack(i + 1, value);
    return dp[i][value] = ans;
}


int main() {
    cin >> n >> w;
    int sum = 0;
    for (int i = 0; i < n; ++i) cin >> items[i].first >> items[i].second, sum += items[i].second;
    for (int i = sum; i >= 0; --i) {
//      search for the first (largest) obtainable value that will fit in W
        if (knapsack(0, i) <= w) {
            cout << i << '\n';
            return 0;
        }
    }
}
