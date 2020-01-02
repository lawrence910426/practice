#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;
const int MAXN = 1e6;
struct area { int l ,r ,u ,d, w; } data[MAXN];
struct event {
    int pos ,u ,d ,w ,type;
    event(int P ,int U ,int D ,int W ,int T): pos(P) ,u(U) ,d(D) ,w(W) ,type(T) {}
};
bool cmp(event a ,event b) { return (a.pos == b.pos ? a.type < b.type : a.pos < b.pos); }
vector<int> x ,y;
vector<event> EQ;
struct seg { int sum ,maxi ,lazy ,L ,R; } segment[MAXN * 5];
static void build(int id ,int L ,int R) {
    segment[id].L = L;
    segment[id].R = R;
    segment[id].sum = segment[id].maxi = segment[id].lazy = 0;
    if(L == R - 1) return;
    build(id * 2 ,L ,(L + R) / 2);
    build(id * 2 + 1 ,(L + R) / 2 ,R);
}
static void push_down(int id) {
    if(segment[id].L != segment[id].R - 1) {
        segment[id * 2].lazy += segment[id].lazy;
        segment[id * 2 + 1].lazy += segment[id].lazy;
    }
    segment[id].sum += (segment[id].R - segment[id].L) * segment[id].lazy;
    segment[id].maxi += segment[id].lazy;
    segment[id].lazy = 0;
}
static void pull_up(int id) {
    if(segment[id].L == segment[id].R - 1) return;
    segment[id].sum = segment[id * 2].sum + segment[id * 2 + 1].sum;
    segment[id].maxi = max(segment[id * 2].maxi, segment[id * 2 + 1].maxi);
}
static void modify(int id ,int L ,int R ,int weight) {
    push_down(id);
    if(R <= segment[id].L || segment[id].R <= L) return;
    if(L <= segment[id].L && segment[id].R <= R) {
        segment[id].lazy += weight;
    } else {
        modify(id * 2 ,L ,R ,weight);
        modify(id * 2 + 1 ,L ,R ,weight);
    }
    pull_up(id);
}

int main() {
    int N ,l ,r ,u ,d ,ans;
    int i;
    while(cin >> N) {
        x = vector<int>() ,y = vector<int>() ,EQ = vector<event>();
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
            EQ.push_back(event(l ,u ,d ,data[i].w ,1));
            EQ.push_back(event(r ,u ,d ,data[i].w ,-1));
        }
        sort(EQ.begin() ,EQ.end() ,cmp);
        build(1 ,0 ,yend - y.begin());
        ans = 0;
        for(event E : EQ) {
            modify(1 ,E.u ,E.d + 1 ,E.w * E.type);
            ans = max(ans ,segment[1].sum + segment[1].maxi);
        }
        cout << ans << endl;
    }
}
