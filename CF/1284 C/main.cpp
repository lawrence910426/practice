#include <iostream>

using namespace std;
const int MAXN = 3e5;
long long N ,mod ,ans;
long long stair[MAXN];
int main() {
    long long i ,tmp1 ,tmp2;
    while(cin >> N >> mod) {
        ans = 0;
        for(stair[0] = i = 1;i <= N;i++) stair[i] = (stair[i - 1] * i) % mod;
        for(i = 1;i <= N;i++) {
            tmp1 = (stair[i] * stair[N - i]) % mod;
            tmp2 = ((N - i + 1) * (N - i + 1)) % mod;
            ans += (tmp1 * tmp2) % mod;
            ans %= mod;
        }
        cout << ans << endl;
    }
}
/*
1 993244853
2 993244853
3 993244853
*/
