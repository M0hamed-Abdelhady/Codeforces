#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()


const int N = 51, F = 1e7 + 3, mod = 1e9 + 7;
int v[N + 1];
int primeFactorsMasks[N + 1];

void sieve() {
    int prime = 0;
    for (int i = 2; i <= N; i++) {
        if (!v[i]) {
            ++prime;
            for (int j = i; j <= N; j += i)
                primeFactorsMasks[j] |= 1 << (prime - 1), v[j] = 1;
        }
    }
}


int count(int mask, int sum, vector<vector<int>> &dp) {
    if (sum == 0)return 1;
    else if (sum < 0)return 0;
    if (dp[sum][mask])return dp[sum][mask];
    int ans = 0;
    for (int j = 1; j <= sum; ++j) {
        int msk = primeFactorsMasks[j];
        if (!(msk & mask)) {
            ans += count(mask | msk, sum - j, dp);
        }
    }
    return dp[sum][mask] = ans;
}


int main() {
    sieve();
    vector<ll> result(51);
    for (int i = 1; i <= 50; ++i) {
        vector<vector<int>> dp(51, vector<int>(1 << 15));
        result[i] = count(0, i, dp);
    }
    for (int i = 1; i < 51; ++i)
        result[i] += result[i - 1];
    int T;
    cin >> T;
    while (T--) {
        int l, r;
        cin >> l >> r;
        cout << result[r] - result[l - 1] << '\n';
    }
    return 0;
}