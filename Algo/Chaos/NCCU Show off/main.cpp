#include <iostream>
#include <memory.h>

using namespace std;
const int MAXN = 1e2 + 50 ,INF = (1LL << 31) - 1;
int N ,raw[MAXN] ,dp[MAXN][MAXN];

int dfs(int l ,int r ,int who) {
    if(l == r - 1) return who * raw[l];
    if(dp[l][r] != INF) return dp[l][r];
    if(who == 1) return dp[l][r] = max(dfs(l + 1 ,r ,-1) + raw[l] ,dfs(l ,r - 1 ,-1) + raw[r - 1]);
    if(who == -1) return dp[l][r] = min(dfs(l + 1 ,r ,1) - raw[l] ,dfs(l ,r - 1 ,1) - raw[r - 1]);
}

int main() {
    int N;
    int i ,j;
    while(cin >> N) {
        for(i = 0;i < MAXN;i++) for(j = 0;j < MAXN;j++) dp[i][j] = INF;
        for(i = 0;i < N;i++) cin >> raw[i];
        cout << (dfs(0 ,N ,1) >= 0 ? "True" : "False") << endl;
    }
}
/*
3
8 95 3
4
17 8 95 3
*/
