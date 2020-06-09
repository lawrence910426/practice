#pragma GCC optimize("Ofast,unroll-loops")
#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 1e6 + 50;
struct zkw {
    int tag[MAXN * 5] ,maxi[MAXN * 5] ,leaf;
    void Pull_Up(int id) {
        maxi[id] = 0;
        if(id * 2 < MAXN * 5) maxi[id] = max(maxi[id] ,maxi[id * 2]);
        if(id * 2 + 1 < MAXN * 5) maxi[id] = max(maxi[id] ,maxi[id * 2 + 1]);
        maxi[id] += tag[id];
    }
    void Modify(int l ,int r ,int val) {
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(l % 2 == 0) { tag[l ^ 1] += val; Pull_Up(l ^ 1); }
            if(r % 2 == 1) { tag[r ^ 1] += val; Pull_Up(r ^ 1); }
            Pull_Up(l); Pull_Up(r);
        }
        for(Pull_Up(r);l != 0;l >>= 1) Pull_Up(l);
    }
    int Query() { return maxi[1]; }
    zkw() {
        memset(tag ,0 ,sizeof(tag)); memset(maxi ,0 ,sizeof(maxi));
        for(leaf = 1;leaf < MAXN + 2;leaf <<= 1) ;
    }
} seg;

bool gin(int &a){
    char c;
    while(c=getchar(),c<'0'||c>'9')if(c==-1)return 0;
    a=c-'0';
    while(c=getchar(),c>='0'&&c<='9')a=a*10+c-'0';
    return 1;
}

struct Rect { int x1 ,y1 ,x2 ,y2 ,wei; } raw[MAXN];
struct Event { int l ,r ,w; };
vector<int> X ,Y;
vector<Event> Process[MAXN];

int main() {
    int N ,ans ,sum; gin(N);
    int i;
    for(i = 0;i < N;i++) {
        gin(raw[i].x1); gin(raw[i].y1); gin(raw[i].x2); gin(raw[i].y2); gin(raw[i].wei);
        X.push_back(raw[i].x1); X.push_back(raw[i].x2);
        Y.push_back(raw[i].y1); Y.push_back(raw[i].y2);
    }
    sort(X.begin() ,X.end()); sort(Y.begin() ,Y.end());
    auto x_last = ++unique(X.begin() ,X.end()) ,y_last = ++unique(Y.begin() ,Y.end());
    for(i = 0;i < N;i++) {
        raw[i].x1 = lower_bound(X.begin() ,x_last ,raw[i].x1) - X.begin();
        raw[i].x2 = lower_bound(X.begin() ,x_last ,raw[i].x2) - X.begin();
        raw[i].y1 = lower_bound(Y.begin() ,y_last ,raw[i].y1) - Y.begin();
        raw[i].y2 = lower_bound(Y.begin() ,y_last ,raw[i].y2) - Y.begin();
    }
    for(i = 0;i < N;i++) {
        seg.Modify(raw[i].y1 ,raw[i].y2 + 1 ,raw[i].wei);
        Process[raw[i].x1].push_back(Event{raw[i].y1 ,raw[i].y2 + 1 ,raw[i].wei});
        Process[raw[i].x2 + 1].push_back(Event{raw[i].y1 ,raw[i].y2 + 1 ,-raw[i].wei});
    }
    ans = seg.Query(); sum = 0;
    for(i = 0;i < x_last - X.begin();i++) {
        for(Event e : Process[i]) { seg.Modify(e.l ,e.r ,-e.w); sum += e.w; }
        ans = max(ans ,seg.Query() + sum);
    }
    cout << ans << endl;
}
