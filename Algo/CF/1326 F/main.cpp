#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;
const int MAXN = 20;
bool know[MAXN][MAXN] ,dp[1 << MAXN][MAXN];
int lazy[MAXN][2] ,ans[1 << MAXN];
int lowbit(int i) { return i & (-i); }
int main() {
    memset(dp ,0 ,sizeof(dp)); memset(lazy ,0 ,sizeof(lazy));
    int N ,items; cin >> N;
    int i ,j; char c;
    for(i = 0;i < N;i++) for(j = 0;j < N;j++) { cin >> c; know[i][j] = (c == '1'); }
    for(i = 0;i < N;i++) dp[1 << i][i] = 1;
    for(i = 1;i < (1 << N);i++) {
        if(lowbit(i) == i) continue;
        vector<int> able;
        for(items = j = 0;j < N;j++) if((i >> j) % 2 == 1) { items += 1; able.push_back(j); }
        for(int a : able) for(int b : able) {
            if(a == b) continue;
            dp[i][a] += dp[i - (1 << a)][b];
            lazy[items - 1][know[a][b]] += dp[i - (1 << a)][b];
        }
    }
    for(i = 1;i < N;i++) cout << lazy[i][0] << " " << lazy[i][1] << endl;
}
