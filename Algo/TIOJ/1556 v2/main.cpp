#pragma GCC optimize("Ofast")
#include <iostream>

using namespace std;

long long N ,i ,j ,ans = 0;
int main() {
    while(cin >> N) {
        for(i = 1;i <= N;i = j + 1) {
            j = N / (N / i);
            ans += (N / i) * (j - i + 1);
        }
        cout << ans - N << '\n';
    }
}
