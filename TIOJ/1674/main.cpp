#pragma GCC optimize("Ofast")
#include <iostream>

using namespace std;
const long long mod = 1e9 + 9;
const long long inv() {
    long long pow = mod - 2 ,tmp = 2 ,ans = 1;
    while(pow > 0) {
        if(pow % 2 == 1) ans = (ans * tmp) % mod;
        tmp = (tmp * tmp) % mod;
        pow >>= 1;
    }
    return ans;
}

long long N ,i ,j ,ans ,sum;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while(cin >> N) {
        ans = (N * N) % mod;
        for(i = 1;i <= N;i = j + 1) {
            j = N / (N / i);
            sum = ((i + j) * inv()) % mod;
            sum = (sum * (j - i + 1)) % mod;
            ans -= ((N / i) * sum) % mod;
            ans = ans % mod;
        }
        ans = (ans + mod) % mod;
        cout << ans << endl;
    }
}
