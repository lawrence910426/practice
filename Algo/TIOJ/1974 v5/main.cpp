#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;
const int MAXN = 1e5 + 50;
struct area { int l ,r ,u ,d ,w; } data[MAXN];
struct event { int pos ,l ,r ,type ,weight; };
bool cmp(event a ,event b) { return a.type > b.type; }
struct seg { int lazy ,maxi; } segment[MAXN * 5];
void push_down(int id ,int l ,int r) {
    segment[id].maxi += segment[id].lazy;
    if(l != r - 1) {
        segment[id * 2].lazy += segment[id].lazy;
        segment[id * 2 + 1].lazy += segment[id].lazy;
    }
    segment[id].lazy = 0;
}
void modify(int id ,int l ,int r ,int ql ,int qr ,int weight) {
    push_down(id ,l ,r);
    if(qr <= l || r <= ql) return;
    if(ql <= l && r <= qr) {
        segment[id].lazy += weight;
        push_down(id ,l ,r);
    } else {
        modify(id * 2 ,l ,(l + r) / 2 ,ql ,qr ,weight);
        modify(id * 2 + 1 ,(l + r) / 2 ,r ,ql ,qr ,weight);
        segment[id].maxi = max(segment[id * 2].maxi ,segment[id * 2 + 1].maxi);
    }
}
vector<event> EQ[MAXN];
int main() {
    int N ,l ,r ,u ,d ,ans ,sum;
    int i;
    while(cin >> N) {
        for(i = 0;i < MAXN;i++) EQ[i] = vector<event>();
        vector<int> x ,y;
        memset(segment ,0 ,sizeof(segment));
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
            EQ[u].push_back(event{u ,l ,r ,1 ,data[i].w});
            EQ[d].push_back(event{d ,l ,r ,-1 ,data[i].w});
        }
        for(auto ES : EQ) sort(ES.begin() ,ES.end() ,cmp);
        for(auto ES : EQ) for(auto E : ES) if(E.type == 1) modify(1 ,0 ,MAXN ,E.l ,E.r ,E.weight);
        sum = 0; ans = max(0 ,segment[1].maxi);
        for(auto ES : EQ) {
            bool executed = false;
            for(i = 0;i < ES.size() && ES[i].type == 1;i++) {
                sum += ES[i].weight;
                modify(1 ,0 ,MAXN ,ES[i].l ,ES[i].r ,-ES[i].weight);
            }
            if(i != 0) {
                ans = max(ans ,segment[1].maxi + sum);
                executed = true;
            }
            for(;i < ES.size();i++) {
                sum -= ES[i].weight;
                modify(1 ,0 ,MAXN ,ES[i].l ,ES[i].r ,ES[i].weight);
            }
            if(!executed) ans = max(ans ,segment[1].maxi + sum);
        }
        cout << ans << endl;
    }
}
