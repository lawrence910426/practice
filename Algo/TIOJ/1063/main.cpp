#include <iostream>

using namespace std;
int raw[300][300] ,dp[300][300];
int main() {
    int N ,M ,ans ,mini;
    int i ,j ,l ,r;
    while(cin >> N >> M) {
        ans = 0;
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) cin >> raw[i][j];
        for(i = 0;i < N;i++) {
            if(i == 0) for(j = 0;j < M;j++) dp[i][j] = raw[i][j];
            else for(j = 0;j < M;j++) dp[i][j] = (raw[i][j] == 0 ? 0 : dp[i - 1][j] + 1);

            for(l = 0;l < M;l++) {
                mini = dp[i][l];
                for(r = l;r < M;r++) {
                    mini = min(mini ,dp[i][r]);
                    ans = max(ans ,mini * (r - l + 1));
                }
            }
        }
        cout << ans << endl;
    }
}
