#include <iostream>
#include <set>
#include <algorithm>
#include <memory.h>
#include <assert.h>

using namespace std;
const int MAXN = 2e4 + 50 ,INF = 1e9;
multiset<int> L ,R ,O;
int prefix[2][MAXN] ,dp[2][MAXN];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,M ,temp ,len ,ans ,l ,r ,o;
    int i ,j;
    while(cin >> N >> M >> len) {
        memset(prefix ,0 ,sizeof(prefix)); memset(dp ,0 ,sizeof(dp)); ans = -1;
        for(prefix[0][0] = i = 0;i < M;i++) { cin >> temp; prefix[0][i + 1] = temp + prefix[0][i]; }
        for(j = 0;j < N;j++) {
            swap(prefix[0] ,prefix[1]); swap(dp[0] ,dp[1]);
            L.clear(); R.clear(); O.clear();
            for(prefix[0][0] = i = 0;i < M;i++) {
                if(j == N - 1) temp = 0;
                else cin >> temp;
                prefix[0][i + 1] = temp + prefix[0][i];
            }
            for(i = 0;i < M;i++) {
                if(i < len && j != 0) R.insert(prefix[1][i] + dp[1][i]);
                else O.insert(dp[1][i]);
            }
            for(i = 0;i < M;i++) {
                l = (L.empty() ? -INF : *L.rbegin()) + prefix[1][min(i + len ,M)];
                r = (R.empty() ? -INF : *R.rbegin()) - prefix[1][i];
                o = (O.empty() ? -INF : *O.rbegin()) + prefix[1][min(i + len ,M)] - prefix[1][i];
                dp[0][i] = prefix[0][min(i + len ,M)] - prefix[0][i] + max({l ,r ,o});

                if(j != 0) {
                    L.insert(- prefix[1][min(i + len ,M)] + dp[1][i]);
                    if(i + len < M) R.insert(prefix[1][i + len] + dp[1][i + len]);
                    if(i - len + 1 >= 0) O.insert(dp[1][i - len + 1]);

                    if(i - len + 1 >= 0) L.erase(L.find(- prefix[1][i + 1] + dp[1][i - len + 1]));
                    R.erase(R.find(prefix[1][i] + dp[1][i]));
                    if(i + len < M) O.erase(O.find(dp[1][i + len]));
                }
            }
        }
        for(i = 0;i < M;i++) ans = max(ans ,dp[0][i]);
        cout << ans << endl;
    }
}
