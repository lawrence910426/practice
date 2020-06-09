#pragma GCC optimize("Ofast")
#include <iostream>
using namespace std;
const int CHEAT = 1e7;
long long N ,l ,r ,mid ,i ,nxt ,ans;
int main() {
    while(cin >> N) {
        ans = 0;
        for(i = 1;i <= N && i <= CHEAT;i++) ans += N / i;
        for(;i <= N;i = nxt) {
            l = i; r = N + 2;
            while(l != r - 1) {
                mid = (l + r) / 2;
                if(N / mid == N / i) l = mid;
                else r = mid;
            }
            nxt = l + 1;
            ans += N / i * (nxt - i);
        }
        cout << ans - N << '\n';
    }
}
