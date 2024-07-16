#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()


const int N = 50 + 3, F = 3e3 + 3, mod = 1e9 + 7;


void solve() {
    ll n, addOn = 0, mxColor = 0;
    cin >> n;
    vector<pair<ll, ll>> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i].first;       // Elements
    for (int i = 0; i < n; ++i) cin >> arr[i].second, mxColor = max(mxColor, arr[i].second);     // Colors
    vector<vector<ll> > prefix(mxColor + 1);
    vector<ll> globalAdd(mxColor + 1);

    for (int j = 0; j < n; ++j) {
//      make prefix sum on each color
        ll lst = 0;
        if (!prefix[arr[j].second].empty())lst = prefix[arr[j].second].back();
        prefix[arr[j].second].push_back(arr[j].first + lst);
    }

    ll q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        ll type, color, c;
        cin >> type >> color >> c;
        if (type == 1) {
//          all elements will be increased by x except for the elements with this color
//          so we add -x on this element so it cancel the addition of addOn
            globalAdd[color] -= c;
            addOn += c;
        } else {
            ll l = 0, r = prefix[color].size() - 1, mid, ans = -1;
            while (l <= r) {
                mid = (l + r) >> 1;
                ll val = prefix[color][mid] + ((mid + 1) * (addOn + globalAdd[color]));
                if (val <= c)ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            cout << ans + 1 << '\n';
        }
    }
}


int main() {
    solve();
    return 0;
}
