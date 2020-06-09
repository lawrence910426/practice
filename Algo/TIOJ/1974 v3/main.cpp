///#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;
const int MAXN = 1e5 + 50;
struct area { int l ,r ,u ,d ,w; } data[MAXN];
struct event {
    int pos ,l ,r ,type ,value;
    event(int P ,int L ,int R ,int T ,int V): pos(P) ,l(L) ,r(R) ,type(T) ,value(V) {}
};
bool cmp(event a ,event b) { return (a.pos == b.pos ? a.type > b.type : a.pos < b.pos); }
struct seg { int lazy ,maxi; } segment[MAXN * 5];
void push_down(int id) {
    segment[id].maxi += segment[id].lazy;
    if(id * 2 + 1 < MAXN * 5) {
        segment[id * 2].lazy += segment[id].lazy;
        segment[id * 2 + 1].lazy += segment[id].lazy;
    }
    segment[id].lazy = 0;
}
void pull_up(int id) { if(id * 2 + 1 < MAXN * 5) segment[id].maxi = max(segment[id * 2].maxi ,segment[id * 2 + 1].maxi); }
void modify(int id ,int l ,int r ,int ql ,int qr ,int weight) {
    if(qr <= l || r <= ql) return;
    if(ql <= l && r <= qr) {
        segment[id].lazy += weight;
        push_down(id);
    } else {
        push_down(id);
        modify(id * 2 ,l ,(l + r) / 2 ,ql ,qr ,weight);
        modify(id * 2 + 1 ,(l + r) / 2 ,r ,ql ,qr ,weight);
        pull_up(id);
    }
}
int main() {
    //ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,ans ,sum ,l ,r ,u ,d ,now;
    int i;
    while(cin >> N) {
        vector<int> x ,y;
        vector<event> EQ;
        for(i = 0;i < N;i++) {
            cin >> data[i].l >> data[i].u >> data[i].r >> data[i].d >> data[i].w;
            x.push_back(data[i].l) ,x.push_back(data[i].r);
            y.push_back(data[i].u) ,y.push_back(data[i].d);
        }
        sort(x.begin() ,x.end()) ,sort(y.begin() ,y.end());
        auto xend = unique(x.begin() ,x.end()) ,yend = unique(y.begin() ,y.end());
        for(i = 0;i < N;i++) {
            l = lower_bound(x.begin() ,xend ,data[i].l) - x.begin();
            r = lower_bound(x.begin() ,xend ,data[i].r) - x.begin();
            u = lower_bound(y.begin() ,yend ,data[i].u) - y.begin();
            d = lower_bound(y.begin() ,yend ,data[i].d) - y.begin();
            EQ.push_back(event(u ,l ,r ,1 ,data[i].w));
            EQ.push_back(event(d ,l ,r ,-1 ,data[i].w));
        }
        sort(EQ.begin() ,EQ.end() ,cmp);
        memset(segment ,0 ,sizeof(segment));
        ans = sum = 0;
        for(event E : EQ) if(E.type == 1) modify(1 ,0 ,xend - x.begin() ,E.l ,E.r + 1 ,E.value);
        for(now = -1 ,i = 0;i < EQ.size();i++) {
            event E = EQ[i];
            if(E.pos != now) {
                ans = max(ans ,segment[1].maxi + sum);
                ans = max(ans ,sum);
                now = E.pos;
            }
            sum += E.value * E.type;
            modify(1 ,0 ,xend - x.begin() ,E.l ,E.r + 1 ,E.type * E.value * (-1));
        }
        cout << ans << '\n';
    }
}
/*
2
0 0 5 5 10
2 2 9 9 20
*/
