#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

const int MAXN = 200+10;
int N ,K ,weight[MAXN] ,dp[MAXN][MAXN] ,temp[MAXN] ,ans;
vector<int> G[MAXN];

void dfs(int parent ,int on) {
    int i ,j;
    dp[on][0] = weight[on];
    for(int V : G[on]) {
        if(V == parent) continue;
        dfs(on ,V);
        for(i = 0;i < MAXN;i++) temp[i] = dp[on][i];
        for(i = 0;i < MAXN;i++) for(j = 0;j < MAXN;j++) if(i + j + 1 > K) temp[min(i ,j + 1)] = max(temp[min(i ,j + 1)] ,dp[on][i] + dp[V][j]);
        for(i = 0;i < MAXN;i++) dp[on][i] = temp[i];
    }
}

int main() {
    int i ,eax ,ebx;
    while(cin >> N >> K) {
        memset(dp ,0 ,sizeof(dp));
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        for(i = 1;i <= N;i++) cin >> weight[i];
        for(i = 0;i < N - 1;i++) {
            cin >> eax >> ebx;
            G[eax].push_back(ebx);
            G[ebx].push_back(eax);
        }
        dfs(-1 ,1);
        for(ans = i = 0;i < N;i++) ans = max(ans ,dp[1][i]);
        cout << ans << endl;
    }
}
