#include <iostream>

using namespace std;
const long long int mod = 1e9 + 7;
int main() {
    long long int T, N ,ans ,tmp;
    for(cin >> T;T--;) {
        cin >> N;
        N -= 1;
        ans = 1;
        tmp = 2;
        for(;N;N >>= 1) {
            if(N & 1) {
                ans *= tmp;
                ans %= mod;
            }
            tmp *= tmp;
            tmp %= mod;
        }
        cout << ans % mod << endl;
    }
}
