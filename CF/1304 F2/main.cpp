#include <iostream>
#include <memory.h>
#include <algorithm>

using namespace std;
const int MAXN = 2e4 + 50 ,INF = 1e9;
int prefix[MAXN];
struct zkw {
    int data[MAXN * 3][2] ,mini[MAXN * 3] ,leaf;
    /* 0-Max ,1-Min */
    void Merge(int i) {
        data[i][0] = max(data[i * 2][0] ,data[i * 2 + 1][0]);
        data[i][1] = min(data[i * 2][1] ,data[i * 2 + 1][1]);
    }
    int Query(int l ,int r ,int type) {
        int ans = (type == 0 ? -INF : INF);
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(type == 0) {
                if(l % 2 == 0) ans = max(ans ,data[l ^ 1][type]);
                if(r % 2 == 1) ans = max(ans ,data[r ^ 1][type]);
            } else {
                if(l % 2 == 0) ans = min(ans ,data[l ^ 1][type]);
                if(r % 2 == 1) ans = min(ans ,data[r ^ 1][type]);
            }
        }
        return ans;
    }
    void Modify(int x ,int diff) {
        x += leaf + 1; data[x][0] += diff; data[x][1] += diff;
        for(x >>= 1;x >= 1;x >>= 1) Merge(x);
    }
    zkw() {
        for(leaf = 1;leaf < MAXN + 2;leaf <<= 1) ;
        for(int i = leaf + 1;i < leaf + 1 + MAXN;i++) data[i][0] = data[i][1] = prefix[i - leaf - 1];
        for(int i = leaf;i >= 1;i--) Merge(i);
    }
} sl ,sr;

int raw[MAXN] ,current[MAXN] ,dp[2][MAXN];
int main() {
    int N ,M ,len ,ans = -INF ,left ,right;
    int i;
    cin >> N >> M >> len; N -= 1;
    memset(dp ,0 ,sizeof(dp)); memset(prefix ,0 ,sizeof(prefix));

    for(i = 0;i < M;i++) cin >> raw[i];
    for(i = current[0] = 0;i < M;i++) current[i + 1] = current[i] + raw[i];
    while(N--) {
        swap(prefix ,current); swap(dp[0] ,dp[1]); sl = zkw(); sr = zkw();
        for(i = 0;i < M;i++) cin >> raw[i];
        for(i = current[0] = 0;i < M;i++) current[i + 1] = current[i] + raw[i];
        for(i = 0;i < M;i++) sr.Modify(i + len ,dp[1][i]);
        for(i = 0;i < M;i++) {
            dp[0][i] = current[min(i + len ,M)] - current[i];
            left = prefix[min(i + len ,M)] - sl.Query(0 ,i ,1);
            right = sr.Query(i ,M ,0) - prefix[i];
            dp[0][i] += max(left ,right);
            sr.Modify(i + len ,-dp[1][i]); sl.Modify(i ,-dp[1][i]);
        }
    }
    for(i = 0;i < M;i++) ans = max(dp[0][i] ,ans);
    cout << ans << endl;
}
/*
prefix[j + len] - prefix[i] + dp[j][1] :i<j
prefix[i + len] - prefix[j] + dp[j][1] :j<i
*/

/*

*/
