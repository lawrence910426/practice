#include <iostream>

using namespace std;
const int MAXN = 16, INF = 1e8;
int dp[1 << MAXN][MAXN][2];
int raw[MAXN];

inline int lowbit(int i) { return i & (-i); }

int main() {
    int N, ans = INF;
    int i, j, k, sum;
    cin >> N;
    for(i = 0;i < N;i++) cin >> raw[i];
    for(i = 0;i < (1 << N);i++) for(j = 0;j < N;j++) { dp[i][j][0] = INF; dp[i][j][1] = 0; }
    for(i = 0;i < N;i++) { dp[1 << i][i][0] = min(0, raw[i]); dp[1 << i][i][1] = max(0, raw[i]); }
    for(i = 3;i < (1 << N);i++) {
        if(i == lowbit(i)) continue;
        for(j = 0;j < N;j++) {
            if((i & (1 << j)) == 0) continue;
            for(sum = k = 0;k < N;k++) if((i & (1 << k)) != 0) sum += raw[k];
            dp[i][j][0] = min(dp[i][j][0], sum);
            for(k = 0;k < N;k++)
                dp[i][j][0] = min(dp[i][j][0], dp[i - (1 << j)][k][0]);
            for(k = 0;k < N;k++)
                dp[i][j][1] = max(dp[i][j][1], dp[i - (1 << j)][k][1]);
            dp[i][j][1] = max(dp[i][j][1], sum - dp[i][j][0]);
        }
    }
    for(j = 0;j < N;j++)
        ans = min(dp[i - 1][j][1], ans);
    cout << ans << endl;
}
