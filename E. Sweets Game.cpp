#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()


const int N = 1 << 19, F = 1e7 + 3, mod = 1e9 + 7;
int dp[N + 1][2];

int input() {
    string s, bin;
    for (int i = 0; i < 5; ++i) {
        getline(cin, s);
        for (const auto &j: s)
            if (j == '.')bin.push_back('0');
            else if (j == 'O')bin.push_back('1');
    }
    int x = 0, value = 1;
    for (auto i = bin.rbegin(); i != bin.rend(); ++i) {
        if (*i == '1')x += value;
        value <<= 1;
    }
    return x;
}

int value(int player) {
    if (player)return 1;
    else return -1;
}

int row(int x) {
    int a = -1;
    if (x >= 17 && x <= 19) a = 4;
    else if (x >= 13 && x <= 16)a = 3;
    else if (x >= 8 && x <= 12)a = 2;
    else if (x >= 4 && x <= 7)a = 1;
    else if (x >= 1 && x <= 3) a = 0;
    return a;
}

bool valid(int grid, int mask) {
    if (((grid & mask) != mask) || !mask)return false;
    int index = 1, tmp = mask, start, patt;
    deque<int> ones;
    while (tmp) {
        if (tmp & 1) ones.push_back(index);
        tmp >>= 1, ++index;
    }
    if (ones.size() == 1)return true;
    bool first = true, can = true;

///   same row
    for (int i = 1; i < ones.size(); ++i) {
        if (ones[i] - ones[i - 1] != 1 || row(ones[i]) != row(ones[i - 1]))can = false;
        if (!can)break;
    }
    if (can)return true;

    ///up right
    can = true;
    pii last = {ones[0], row(ones[0])};
    for (int i = 1; i < ones.size(); ++i) {
        int r = row(ones[i]);
        if (r - last.second != 1)can = false;
        if (last.second == 0 || last.second == 3) {
            if (ones[i] - last.first != 3)can = false;
        } else if (last.second == 1 || last.second == 2)
            if (ones[i] - last.first != 4)can = false;
        last = {ones[i], r};
    }
    if (can)return true;

    ///up left
    can = true;
    last = {ones[0], row(ones[0])};
    for (int i = 1; i < ones.size(); ++i) {
        int r = row(ones[i]);
        if (r - last.second != 1)can = false;
        if (last.second == 0 || last.second == 3) {
            if (ones[i] - last.first != 4)can = false;
        } else if (last.second == 1 || last.second == 2)
            if (ones[i] - last.first != 5)can = false;
        last = {ones[i], r};
    }
    return can;
}

vector<int> validMasks;

void findValidMasks(int grid) {
    for (int mask = 1; mask <= 1 << 19; ++mask)
        if (valid(grid, mask))validMasks.push_back(mask);
}

int minmax(int grid, int player) {
    if (grid == 0)return value(player);
    if (dp[grid][player])return dp[grid][player];
    if (!player) {
        int ans = -1;
        for (const auto &mask: validMasks) {
            if ((grid & mask) == mask) {
                ans = minmax(grid & ~mask, 1 - player);
            }
            if (ans == 1)break;
        }
        return dp[grid][player] = ans;
    } else {
        int ans = 1;
        for (const auto &mask: validMasks) {
            if ((grid & mask) == mask) {
                ans = minmax(grid & ~mask, 1 - player);
            }
            if (ans == -1)break;
        }
        return dp[grid][player] = ans;
    }
}


int main() {
    int grid = input();
    findValidMasks(grid);
    if (minmax(grid, 0) > 0)cout << "Karlsson\n";
    else cout << "Lillebror\n";
    return 0;
}
