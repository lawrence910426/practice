#include <iostream>
#include <memory.h>

using namespace std;
const int MAXN = 1e2 + 5;
long long dp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    long long N ,i ,j ,k ,tmp;
    while(cin >> N) {
        memset(dp ,-1, sizeof(dp));
        for(i = 0;i < N;i++) cin >> dp[i][i + 1];
        for(i = 2;i <= N;i++) for(j = 0;j + i <= N;j++) for(k = 1;k < i;k++) {
            if(i % 2 == 1) tmp = dp[j][j + k] * dp[j + k][j + i];
            else tmp = dp[j][j + k] + dp[j + k][j + i];
            dp[j][j + i] = max(dp[j][j + i] ,tmp);
        }
        cout << dp[0][N] << '\n';
    }
}
