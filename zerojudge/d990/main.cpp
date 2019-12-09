#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 1e7;
int Z[MAXN];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    string big ,small ,concat;
    int N ,i ,L ,R ,K ,ans;
    cin >> big;
    for(cin >> N;N--;) {
        cin >> small;
        concat = small + '$' + big;
        L = R = ans = Z[0] = 0;
        for(i = 1;i < concat.size();i++) {
            if(R < i) {
                L = R = i;
                while(R < concat.size() && concat[R] == concat[R - L]) R += 1;
                Z[i] = R - L;
            } else {
                K = i - L;
                if(Z[K] <= R - i) {
                    L = R = i;
                    while(R < concat.size() && concat[R] == concat[R - L]) R += 1;
                    Z[i] = R - L;
                } else Z[i] = Z[K];
            }
        }
        for(i = 0;i < concat.size();i++) if(Z[i] == small.size()) ans += 1;
        cout << ans << endl;
    }
}
