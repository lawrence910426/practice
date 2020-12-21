#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
const long long mod = 1e9 + 7, MAXN = 1e6 + 50;

string X;

int main() {
    long long T, N, i, j, k, last, ans;
    for(cin >> T;T--;) {
        cin >> N >> X;
        ans = X.size();
        for(i = 1;i <= N;i++) {
            last = X.size();
            for(k = 1;k < X[i - 1] - '0';k++) for(j = i;j < last && X.size() < MAXN;j++) X += X[j];
            ans = (i + (X[i - 1] - '0') * (ans - i)) % mod;
            ans = (ans + mod) % mod;
        }
        cout << ans << endl;
    }
}
