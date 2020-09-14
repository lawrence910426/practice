#include <iostream>
#include <cstring>
#include <memory.h>
#include <algorithm>

using namespace std;
const int MAXN = 205;
int dp[2][MAXN][MAXN];

int main() {
    int N, K, ans = -1;
    string s, t;
    int i, j, k;
    cin >> N >> K >> s >> t;

    if(t[0] == t[1]) {
        for(ans = i = 0;i < N;i++) ans += (s[i] == t[0] ? 1 : 0);
        ans = min(ans + K, N);
        ans = ans * (ans - 1) / 2;
    } else {
        memset(dp[1], -1 ,sizeof(dp[1]));
        for(j = 0;j <= K;j++) dp[1][j][0] = 0;

        for(i = 0;i < N;i++) {
            memset(dp[0], -1, sizeof(dp[0]));
            for(j = 0;j <= K;j++) dp[1][j][0] = 0;

            for(j = 0;j <= K;j++) for(k = 0;k < N;k++) {
                if(s[i] == t[0]) {
                    if(k != 0) dp[0][j][k] = dp[1][j][k - 1];

                    if(j != 0) {
                        dp[0][j][k] = max(dp[0][j][k], dp[1][j - 1][k]);
                        if(dp[1][j - 1][k] != -1) dp[0][j][k] = max(dp[0][j][k], dp[1][j - 1][k] + k);
                    }
                } else if(s[i] == t[1]) {
                    if(dp[1][j][k] != -1) dp[0][j][k] = dp[1][j][k] + k;

                    if(j != 0) {
                        if(k != 0) dp[0][j][k] = max(dp[0][j][k], dp[1][j - 1][k - 1]);
                        dp[0][j][k] = max(dp[0][j][k], dp[1][j - 1][k]);
                    }
                } else {
                    dp[0][j][k] = dp[1][j][k];

                    if(j != 0) {
                        if(k != 0) dp[0][j][k] = max(dp[0][j][k], dp[1][j - 1][k - 1]);
                        if(dp[1][j - 1][k] != -1) dp[0][j][k] = max(dp[0][j][k], dp[1][j - 1][k] + k);
                    }
                }
            }
            swap(dp[0], dp[1]);
        }
        for(j = 0;j <= K;j++) for(k = 0;k < N;k++) ans = max(dp[1][j][k], ans);
    }

    cout << ans << endl;
}
