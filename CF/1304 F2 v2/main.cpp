#include <iostream>
#include <set>
#include <algorithm>
#include <memory.h>
using namespace std;

const int MAXN = 2e4 + 50 ,INF = 1e9;
multiset<int> A ,B ,C ,D;
int prefix[2][MAXN] ,input ,dp[2][MAXN];
int main() {
    int N ,M ,len ,a ,b ,c ,d ,ans = -INF;
    int i;
    cin >> N >> M >> len;
    memset(prefix ,0 ,sizeof(prefix)); memset(dp ,0 ,sizeof(dp));

    for(i = prefix[0][0];i < M;i++) { cin >> input; prefix[0][i + 1] = prefix[0][i] + input; }
    swap(prefix[0] ,prefix[1]);
    if(N != 1) for(i = prefix[0][0];i < M;i++) { cin >> input; prefix[0][i + 1] = prefix[0][i] + input; }
    for(i = 0;i < M;i++) dp[0][i] = prefix[0][min(i + len ,M)] - prefix[0][i] + prefix[1][min(i + len ,M)] - prefix[1][i];
    N -= 1;

    while(N--) {
        swap(prefix[0] ,prefix[1]); swap(dp[0] ,dp[1]);
        A.clear(); B.clear(); C.clear(); D.clear();
        for(i = prefix[0][0];i < M;i++) { if(N == 0) input = 0; else cin >> input; prefix[0][i + 1] = prefix[0][i] + input; }
        for(i = 0;i < M;i++) {
            if(i < len) C.insert(prefix[1][i] + dp[1][i]);
            else D.insert(dp[1][i]);
        }
        for(i = 0;i < M;i++) {
            a = (A.empty() ? -INF : *A.rbegin()) + prefix[1][min(i + len ,M)] - prefix[1][i];
            b = (B.empty() ? -INF : *B.rbegin()) + prefix[1][min(i + len ,M)];
            c = (C.empty() ? -INF : *C.rbegin()) - prefix[1][i];
            d = (D.empty() ? -INF : *D.rbegin()) + prefix[1][min(i + len ,M)] - prefix[1][i];
            dp[0][i] = prefix[0][min(M ,i + len)] - prefix[0][i];
            dp[0][i] += max({a ,b ,c ,d});

            if(i - len + 1 >= 0) A.insert(dp[1][i - len + 1]);
            B.insert(- prefix[1][min(i + len ,M)] + dp[1][i]);
            if(i + len < M) C.insert(prefix[1][i + len] + dp[1][i + len]);

            if(i - len + 1 >= 0) B.erase(B.find(- prefix[1][i + 1] + dp[1][i - len + 1]));
            C.erase(C.find(prefix[1][i] + dp[1][i]));
            if(i + len < M) D.erase(D.find(dp[1][i + len]));
        }
    }
    for(i = 0;i < M;i++) ans = max(ans ,dp[0][i]);
    cout << ans << endl;
}

/*
A dp[1][j]
B prefix[i + len] - prefix[j + len] + dp[1][j]
C prefix[j] - prefix[i] + dp[1][j]
D dp[1][j]
*/

/*
3 5 2
0 2 1 1 0
0 0 3 1 2
1 0 4 3 1
*/
