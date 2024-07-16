#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()


const int N = 2e2 + 3, F = 1e5 + 1, mod = 1e9 + 7;
ll dp[101][F], n, w;
vector<pair<ll, ll>> items(N);


ll knapsack(ll i, ll sum) {
    if (i == n || sum == w)return 0;
    if (dp[i][sum])return dp[i][sum];
    ll ans = 0;
    if (sum + items[i].first <= w)
        ans = max(knapsack(i + 1, sum + items[i].first) + items[i].second, knapsack(i + 1, sum));
    else ans = knapsack(i + 1, sum);
    return dp[i][sum] = ans;
}


int main() {
    cin >> n >> w;
    for (int i = 0; i < n; ++i) cin >> items[i].first >> items[i].second;
    cout << knapsack(0, 0) << '\n';
}
