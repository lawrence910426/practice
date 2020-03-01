#include <iostream>
#include <map>
#include <algorithm>

const int MAXN = 1e2 + 50;
using namespace std;
struct seg {
    int l ,r;
    seg operator+(const seg& s) const { return seg{max(s.l ,l) ,min(s.r ,r)}; }
} limit[MAXN];
map<int ,seg> mapa; int time[MAXN] = {0};
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int Q ,N ,Epoch ,S;
    int i ,l ,r ,t ,diff;
    for(cin >> Q;Q--;) {
        cin >> N >> S; mapa = map<int ,seg>();
        for(i = 0;i < N;i++) {
            cin >> t >> l >> r;
            if(mapa.find(t) == mapa.end()) mapa[t] = seg{l ,r};
            else mapa[t] = mapa[t] + seg{l ,r};
        }
        Epoch = 1; limit[0].l = limit[0].r = S;
        for(auto p : mapa) { time[Epoch] = p.first; limit[Epoch] = p.second; Epoch += 1; }
        for(i = 1;i < Epoch;i++) {
            diff = time[i] - time[i - 1];
            limit[i] = seg{limit[i - 1].l - diff ,limit[i - 1].r + diff} + limit[i];
            if(limit[i].l > limit[i].r) break;
        }
        cout << (i == Epoch ? "Yes" : "No") << endl;
    }
}
