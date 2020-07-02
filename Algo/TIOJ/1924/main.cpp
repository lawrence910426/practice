#pragma GCC optimize("Ofast")

#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 2e6 + 50;
int N, prefix[3][MAXN], raw[MAXN];
inline int sum(int type, int l, int r) { return prefix[type][r] - prefix[type][l]; }

int maximum(int permu[3]) {
    int ans = -1, maxi = 0;
    for(int i = 0;i < N;i++) {
        maxi = max(maxi, sum(permu[0], 0, i) - prefix[permu[1]][i]);
        ans = max(ans, maxi + prefix[permu[1]][i] + sum(permu[2], i, N));
    }
    return ans;
}

int main() {
    int ans = -1, permu[3] = {0, 1, 2};
    char c; int i, j;
    cin >> N;
    for(i = 0;i < N;i++) {
        cin >> c;
        if(c == 'P') raw[i] = 0;
        if(c == 'E') raw[i] = 1;
        if(c == 'C') raw[i] = 2;
    }
    for(j = 0;j < 3;j++) prefix[j][0] = 0;
    for(i = 0;i < N;i++) for(j = 0;j < 3;j++) prefix[j][i + 1] = prefix[j][i] + (raw[i] == j ? 1 : 0);
    do { ans = max(ans, maximum(permu)); } while(next_permutation(permu, permu + 3));
    cout << ans << endl;
}
