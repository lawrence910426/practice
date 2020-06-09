#pragma GCC optimize("Ofast")
#include <iostream>
#include <set>
using namespace std;
const int MAXN = 1e6 + 50;
int tim[MAXN] ,par[MAXN];
set<int> S;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N ,val ,i; cin >> N;
    tim[0] = -1; tim[N + 1] = -2;
    S.insert(0); S.insert(N + 1);
    for(i = 0;i < N;i++) {
        cin >> val;
        set<int>::iterator l ,r = S.lower_bound(val);
        l = prev(r);
        if(tim[*l] < tim[*r]) par[val] = *r;
        else par[val] = *l;
        S.insert(val); tim[val] = i;
    }
    for(i = 1;i <= N;i++) cout << par[i] << '\n';
}
