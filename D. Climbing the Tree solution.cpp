#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()


const int N = 2e5 + 3, F = 1e6 + 3, mod = 1e9 + 7;


bool intersect(pair<ll, ll> &a, pair<ll, ll> &b) {
/// Given two ranges a and b, is a and b intersect ?
    return ((b.first >= a.first && b.first <= a.second) || (b.second >= a.first && b.second <= a.second) ||
            (a.first >= b.first && a.second <= b.second));
}

ll solution(ll &a, ll &b, ll &c) {
//    (a - b) * n + a >= c
/// Given a, b and c find smallest n
    if (a >= c)return 1;
    ll x = (c - a), y = a - b, n = x / y;
    return (x % y ? n + 2 : n + 1);
}

void solve() {
    ll q;
    cin >> q;
///    The initial range of the height of the tree
    pair<ll, ll> currentHeight = {LLONG_MIN, LLONG_MAX};
    while (q--) {
        ll type, a, b, n;
        cin >> type;
        if (type == 1) {
            cin >> a >> b >> n;
            pair<ll, ll> newHeight;
///         The new range of the height of the tree according to the query
            if (n >= 2)newHeight = {(a - b) * (n - 2) + a + 1, (a - b) * (n - 1) + a};
            else newHeight = {1, a};
            if (intersect(currentHeight, newHeight)) {
///          if the new range intersect with the current range update current range else ignore it
                currentHeight = {max(currentHeight.first, newHeight.first),
                                 min(currentHeight.second, newHeight.second)};
                cout << "1 ";
            } else cout << "0 ";
        } else {
            cin >> a >> b;
///          find solution for n days that needed to climb equal to the upper boundary of current range or more
            n = solution(a, b, currentHeight.second);
            if (n == 1) {
                cout << n << ' ';
                continue;
            }
            ll last = (a - b) * (n - 2) + a;
///          check if the solution when find cover all the current range
///          so that we make sure whatever the value of h in this range the solution will be true always
            if (last < currentHeight.first)cout << n << ' ';
            else cout << "-1 ";
        }
    }
    cout << '\n';
}


int main() {
    int T;
    cin >> T;
    while (T--)solve();
    return 0;
}