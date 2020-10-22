#pragma GCC optimize("Ofast")

#include <iostream>
#include <cstring>

using namespace std;
const int MAXN = 1e4 + 50;
int Z[MAXN], prefix[MAXN];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string hay, needle, S;
    int Q, L, R, l, r, i, ans;
    while(cin >> hay >> needle >> Q) {
        S = needle + '$' + hay;
        for(L = R = i = 1;i < S.size();i++) {
            if(i >= R) {
                L = R = i;
                while(R < S.size() && S[R - L] == S[R]) R += 1;
                Z[i] = R - L;
            } else {
                if(Z[i - L] < R - i) Z[i] = Z[i - L];
                else {
                    L = i;
                    while(R < S.size() && S[R - L] == S[R]) R += 1;
                    Z[i] = R - L;    
                }
            }
        }

        for(prefix[0] = i = 0;i < hay.size();i++) prefix[i + 1] = prefix[i] + (Z[i + needle.size() + 1] == needle.size() ? 1 : 0);
        for(ans = 0;Q--;) {
            cin >> l >> r;
            if(r - needle.size() + 1 < 1) continue;
            ans = max(ans, prefix[r - needle.size() + 1] - prefix[l - 1]);
        }
        cout << ans << '\n';
    }
}
