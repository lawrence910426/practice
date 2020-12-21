#pragma GCC optimize("Ofast")

#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;
const int MAXN = 2e5 + 50, MAXC = 10;

int raw[MAXN], K;

int TimesTen(int x) {
    int ans = 0, temp = x;
    ans = temp = (temp << 1) % K; /* 2 */
    temp = (temp << 1) % K; /* 4 */
    temp = (temp << 1) % K; /* 8 */
    ans = (ans + temp) % K;
    return ans;
}

int Log(int x) {
    int ans = 0;
    for(;x > 0;x /= 10) ans += 1;
    return ans;
}

unordered_map<int, int> modulo[MAXC];
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    long long ans;
    int N;
    int i, j, temp, digit;
    while(cin >> N >> K) { 
        for(j = 0;j < MAXC;j++) modulo[j].clear();
        for(i = 0;i < N;i++) cin >> raw[i];
        for(i = 0;i < N;i++) {
            temp = raw[i];
            for(j = 0;j < MAXC;j++) {
                temp = TimesTen(temp);
                modulo[j][temp] = modulo[j][temp] + 1;
            }
        }
        ans = 0;
        for(i = 0;i < N;i++) { 
            digit = Log(raw[i]);
            temp = raw[i];
            ans += (long long)modulo[digit][((K - raw[i]) % K + K) % K];
            for(j = 0;j < digit;j++) temp = TimesTen(temp);
            ans -= (temp + raw[i]) % K == 0 ? 1LL : 0LL;
        }
        cout << ans << '\n';
    }
}
