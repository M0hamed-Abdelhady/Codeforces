#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()


const int N = 50 + 3, F = 3e3 + 3, mod = 1e9 + 7;

string a, b;
int dp[F][F];

int LCS(int i, int j) {
    if (i == a.size() || j == b.size()) return 0;
    if (~dp[i][j])return dp[i][j];
    if (a[i] == b[j]) dp[i][j] = LCS(i + 1, j + 1) + 1;
    else return dp[i][j] = max(LCS(i + 1, j), LCS(i, j + 1));
    return dp[i][j];
}


int main() {
    cin >> a >> b;
//  find LCS(a, b) => The Longest Common Subsequence of the string a and b
    memset(dp, -1, sizeof dp);
    int mxLen = LCS(0, 0);
    int i = 0, j = 0;
    string c;
    while (mxLen) {
        if (a[i] == b[j])c.push_back(a[i]), ++i, ++j, --mxLen;
        else {
            if (dp[i + 1][j] >= dp[i][j + 1])++i;
            else ++j;
        }
    }
    cout << c << '\n';
}