#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;
const int MAXN = 1e4 + 50;
struct area { int l ,r ,u ,d, w; } data[MAXN];
struct event {
    int pos ,l ,r ,w ,type;
    event(int P ,int L ,int R ,int W ,int T): pos(P) ,l(L) ,r(R) ,w(W) ,type(T) {}
};
bool cmp(event a ,event b) { return (a.pos == b.pos ? a.type > b.type : a.pos < b.pos); }
vector<int> x ,y;
vector<event> EQ;
struct seg {
    int l ,r
};

int main() {
    int N ,l ,r ,u ,d;
    int i;
    long long ans ,sum ,temp;
    while(cin >> N) {
        x = y = vector<int>() ,EQ = vector<event>();
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
        segment = zkw(N) ,sum = ans = 0;
        for(event E : EQ) if(E.type == 1) segment.modify(E.l ,E.r + 1 ,E.w);
        for(event E : EQ) {
            temp = E.r - E.l ,temp *= E.w ,temp *= E.type;
            sum += temp;
            segment.modify(E.l ,E.r + 1 ,E.w * E.type * (-1LL));
            ans = max(ans ,segment.maxi[1] + sum);
        }
        cout << ans << endl;
    }
}
