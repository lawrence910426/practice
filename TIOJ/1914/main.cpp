#include <iostream>

using namespace std;
const int MAXN = 2e2 + 10;
int raw[MAXN] ,data[MAXN] ,dp[MAXN][MAXN];
int main() {
    int T ,N ,M ,ptr;
    int i ,j ,k;
    for(cin >> T;T--;) {
        cin >> N >> M;
        for(i = 0;i < N;i++) cin >> raw[i];
        for(i = 0;i < MAXN;i++) for(j = 0;j < MAXN;j++) dp[i][j] = (1LL << 31) - 1;
        data[0] = raw[0];
        for(i = ptr = 1;i < N;i++) if(raw[i] != raw[i - 1]) data[ptr++] = raw[i];
        for(i = 0;i < ptr;i++) dp[i][i + 1] = 1;
        for(i = 2;i <= ptr;i++) for(j = 0;j + i <= ptr;j++) for(k = 1;k < i;k++) {
            dp[j][j + i] = min(dp[j][j + i] ,dp[j][j + k] + dp[j + k][j + i] - (data[j] == data[j + i - 1] ? 1 : 0));
        }
        cout << dp[0][ptr] << endl;
    }
}
