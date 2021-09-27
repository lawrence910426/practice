#pragma GCC optimize("Ofast")

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;
const int MAXN = 2e5 + 50, MAXC = 10;

int raw[MAXN], K;
int modulo[MAXC][MAXN], last[MAXC];

inline int TimesTen(int x) {
    int ans = 0, temp = x;
    ans = temp = (temp << 1) % K; /* 2 */
    temp = (temp << 1) % K; /* 4 */
    temp = (temp << 1) % K; /* 8 */
    ans = (ans + temp) % K;
    return ans;
}

inline int Log(int x) {
    int ans = 0;
    for(;x > 0;x /= 10) ans += 1;
    return ans;
}

inline int amount(int digit, int value) {
    digit -= 1;
    int* l = lower_bound(modulo[digit], modulo[digit] + last[digit], value);
    int* r = upper_bound(modulo[digit], modulo[digit] + last[digit], value);
    return r - l;
}

inline int nextint() {
    int x = 0, c = getchar(), neg = false;
    while(('0' > c || c > '9') && c!='-' && c!=EOF) c = getchar();
    if(c == '-') neg = true, c = getchar();
    while('0' <= c && c <= '9') x = x*10 + (c^'0'), c = getchar();
    if(neg) x = -x;
    return x; // returns 0 if EOF
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    long long ans;
    int N;
    int i, j, temp, digit;
    while(N = nextint()) {
        K = nextint(); 
        for(j = 0;j < MAXC;j++) last[j] = 0;
        for(i = 0;i < N;i++) raw[i] = nextint();
        for(i = 0;i < N;i++) {
            temp = raw[i];
            for(j = 0;j < MAXC;j++) {
                modulo[j][last[j]] = temp = TimesTen(temp);
                last[j] += 1;
            }
        }
        for(j = 0;j < MAXC;j++) sort(modulo[j], modulo[j] + last[j]);
        ans = 0;
        for(i = 0;i < N;i++) { 
            digit = Log(raw[i]);
            temp = raw[i];
            ans += (long long)amount(digit, (K - (raw[i] % K)) % K);
            for(j = 0;j < digit;j++) temp = TimesTen(temp);
            ans -= (temp + raw[i]) % K == 0 ? 1LL : 0LL;
        }
        cout << ans << '\n';
    }
}
