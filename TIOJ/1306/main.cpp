#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 1e7;
int Z[MAXN];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    string big ,small ,concat;
    int T ,Q ,ans;
    int i ,L ,R ,k;
    for(cin >> T;T--;) {
        cin >> big;
        for(cin >> Q;Q--;) {
            cin >> small;
            concat = small + '$' + big;
            ans = Z[0] = 0;
            for(i = 1 ,L = R = 0;i < concat.size();i++) {
                if(R < i) {
                    L = R = i;
                    while(R < concat.size() && concat[R] == concat[R - L]) R += 1;
                    Z[i] = R - L;
                } else {
                    k = i - L;
                    if(Z[k] >= R - i) {
                        L = R = i;
                        while(R < concat.size() && concat[R] == concat[R - L]) R += 1;
                        Z[i] = R - L;
                    } else {
                        Z[i] = Z[k];
                    }
                }
            }
            for(i = 0;i < concat.size();i++) if(Z[i] == small.size()) ans += 1;
            cout << ans << '\n';
            /*for(i = 0;i < concat.size();i++) cout << concat[i] << "\t";
            cout << endl;
            for(i = 0;i < concat.size();i++) cout << Z[i] << "\t";
            cout << endl;*/
        }
    }
}
// I guess it needs an AC_Automaton
