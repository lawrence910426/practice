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
bool cmp(event a ,event b) { return a.type > b.type; }
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
void test() {
    int l ,r ,w;
    while(cin >> l >> r >> w) {
        modify(1 ,0 ,MAXN ,l ,r ,w);
        cout << segment[1].maxi << endl;
    }
}
vector<event> EQ[MAXN];
int main() {
    //test();
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,ans ,sum ,l ,r ,u ,d;
    int i ,ptr;
    cin >> N;
    vector<int> x ,y;
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
        EQ[u].push_back(event(u ,l ,r ,1 ,data[i].w));
        EQ[d].push_back(event(d ,l ,r ,-1 ,data[i].w));
    }
    memset(segment ,0 ,sizeof(segment));
    ans = sum = 0;
    for(auto ES : EQ) sort(ES.begin() ,ES.end() ,cmp);
    for(auto ES : EQ) for(auto E : ES) if(E.type == 1) modify(1 ,0 ,xend - x.begin() ,E.l ,E.r + 1 ,E.value);
    for(ptr = 0;ptr < MAXN;ptr++) {
        auto ES = EQ[ptr];
        for(i = 0;i < ES.size() && ES[i].type == 1;i++) {
            sum += ES[i].value * ES[i].type;
            modify(1 ,0 ,xend - x.begin() ,ES[i].l ,ES[i].r + 1 ,ES[i].type * ES[i].value * (-1));
        }
        ans = max(ans ,segment[1].maxi + sum);
        for(;i < ES.size();i++) {
            sum += ES[i].value * ES[i].type;
            modify(1 ,0 ,xend - x.begin() ,ES[i].l ,ES[i].r + 1 ,ES[i].type * ES[i].value * (-1));
        }
    }
    cout << ans << '\n';
}
/*
2
0 0 5 5 10
2 2 9 9 20
*/
