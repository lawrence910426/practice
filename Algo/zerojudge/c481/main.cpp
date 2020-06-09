#include <iostream>
#include <memory.h>

using namespace std;
const int MAXN = 205;
int data[MAXN] ,dp[MAXN][MAXN];
int main() {
    int T ,N ,M;
    int i ,j ,k;
    for(cin >> T;T--;) {
        cin >> N >> M;
        for(i = 0;i < MAXN;i++) for(j = 0;j < MAXN;j++) dp[i][j] = MAXN * 100;
        for(i = 0;i < N;i++) cin >> data[i];
        for(i = 0;i < N;i++) dp[i][i + 1] = 1;
        for(i = 2;i <= N;i++) for(j = 0;j + i <= N;j++) for(k = j + 1;k < j + i;k++)
            dp[j][j + i] = min(dp[j][j + i] ,dp[j][k] + dp[k][j + i] + (data[j] == data[j + i - 1] ? -1 : 0));
        cout << dp[0][N] << endl;
    }
}
