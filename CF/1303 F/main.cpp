#pragma GCC optimize("Ofast,unroll-loops")
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

const int MAXQ = 2e6 + 50 ,MAXN = 3e2 + 50;

int N ,M ,Q ,mapa[MAXN][MAXN] ,dx[4] = {0 ,0 ,1 ,-1} ,dy[4] = {1 ,-1 ,0 ,0} ,prefix[MAXQ];
struct { int x ,y ,c ,ans; } Query[MAXQ];
struct { vector<int> in ,out; } Event[MAXQ];
struct Joint {
    int boss[MAXN * MAXN];
    inline int Query(int x) { return (boss[x] == x ? x : boss[x] = Query(boss[x])); }
    inline bool Join(int a ,int b) { a = Query(a); b = Query(b); boss[a] = b; return a != b; }
    Joint() { for(int i = 0;i < MAXN * MAXN;i++) boss[i] = i; }
} DSU;

bitset<MAXN * MAXN> used;
inline void Process(vector<int> &V ,int style) {
    DSU = Joint(); used.reset();
    if(style == -1) reverse(V.begin() ,V.end());
    int diff ,x ,y ,xx ,yy;
    for(int i : V) {
        diff = 1; x = Query[i].x; y = Query[i].y; used[x * M + y] = true;
        for(int k = 0;k < 4;k++) {
            xx = x + dx[k]; yy = y + dy[k];
            if(xx < 0 || xx >= N || yy < 0 || yy >= M || !used[xx * M + yy]) continue;
            if(DSU.Join(x * M + y ,xx * M + yy)) diff -= 1;
        }
        prefix[i] += diff * style;
    }
}

inline void gin(int &a){ a = 0; for(char c;c = getchar() ,c >= '0' && c <= '9';a = a * 10 + c - '0') ; }

int main() {
    int i ,colors = -1 ,pole ,ans;
    memset(prefix ,0 ,sizeof(prefix));
    gin(N); gin(M); gin(Q);
    for(i = 0;i < N * M;i++) {
        Query[i].x = i / M; Query[i].y = i % M; Query[i].c = 0;
        mapa[Query[i].x][Query[i].y] = Query[i].c;
        Event[Query[i].c].in.push_back(i);
    }
    for(pole = i;i < Q + pole;i++) {
        gin(Query[i].x); gin(Query[i].y); gin(Query[i].c); Query[i].x -= 1; Query[i].y -= 1;
        Event[mapa[Query[i].x][Query[i].y]].out.push_back(i);
        mapa[Query[i].x][Query[i].y] = Query[i].c;
        Event[Query[i].c].in.push_back(i);
        colors = max(colors ,Query[i].c); Query[i].ans = 0;
    }
    for(pole = i;i < N * M + pole;i++) {
        Query[i].x = (i - pole) / M; Query[i].y = (i - pole) % M;
        Event[mapa[Query[i].x][Query[i].y]].out.push_back(i);
    }
    for(i = 0;i <= colors;i++) {
        if(!Event[i].in.empty()) Process(Event[i].in ,1);
        if(!Event[i].out.empty()) Process(Event[i].out ,-1);
    }
    for(ans = i = 0;i < Q + 2 * N * M;i++) { ans += prefix[i]; if(N * M <= i && i < N * M + Q) cout << ans << '\n'; }
}
