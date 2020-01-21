#include <iostream>
#include <memory.h>
using namespace std;
const long long mod = 1e9 + 7 ,MAXN = 3e3 + 50;
long long N ,M ,pascal[MAXN][MAXN];
long long power(long long base ,long long pow) {
    long long ans = 1, tmp = base;
    for(;pow != 0;pow >>= 1) {
        if(pow % 2 == 1) ans = (ans * tmp) % mod;
        tmp = (tmp * tmp) % mod;
    }
    return ans % mod;
}
void build() {
    int i ,j;
    memset(pascal ,0 ,sizeof(pascal));
    pascal[0][0] = pascal[1][0] = pascal[1][1] = 1;
    for(i = 2;i < MAXN;i++) for(j = 0;j < MAXN;j++)
        pascal[i][j] = (j == 0 ? 1 : (pascal[i - 1][j - 1] + pascal[i - 1][j]) % mod);
}
int main() {
    int i ,j;
    long long ans ,tmp;
    build();
    while(cin >> N >> M) {
        ans = 0;
        for(i = 0;i < N;i++) {
            tmp = (pascal[M + i - 1][i] * pascal[M + N - i - 1][N - i - 1]) % mod;
            ans = (ans + tmp) % mod;
        }
        cout << ans << endl;
    }
}
