#pragma GCC optimize("Ofast")
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>

using namespace std;

const int MAXN = 1e4 + 50 ,MAXM = 5e4 + 50 ,MAXV = MAXN + MAXM;
class LCT {
    int ch[MAXV][2] ,par[MAXV] ,rev[MAXV] ,maxi[MAXV] ,val[MAXV];
    inline bool Is_Root(int x) { return par[x] == -1 || (ch[par[x]][0] != x && ch[par[x]][1] != x); }
    inline int Get_Child(int x) { return ch[par[x]][1] == x ? 1 : 0; }
    inline void Send(int x) { swap(ch[x][0] ,ch[x][1]); rev[x] ^= 1; }
    inline void Push_Down(int x) {
        if(rev[x]) {
            if(ch[x][0] != -1) Send(ch[x][0]);
            if(ch[x][1] != -1) Send(ch[x][1]);
            rev[x] = 0;
        }
    }
    inline void Pull_Up(int x) {
        maxi[x] = val[x];
        if(ch[x][0] != -1) maxi[x] = max(maxi[x] ,maxi[ch[x][0]]);
        if(ch[x][1] != -1) maxi[x] = max(maxi[x] ,maxi[ch[x][1]]);
    }
    inline void Update(int x) {
        if(!Is_Root(x)) Update(par[x]);
        Push_Down(x);
    }
    inline void Rotate(int x) {
        int p = par[x] ,pp = par[p] ,style = Get_Child(x) ,subtree = ch[x][style ^ 1];
        par[x] = pp;
        if(!Is_Root(p)) ch[pp][Get_Child(p)] = x;
        ch[p][style] = subtree;
        if(subtree != -1) par[subtree] = p;
        ch[x][style ^ 1] = p;
        par[p] = x;
        Pull_Up(p); Pull_Up(x);
        if(pp != -1) Pull_Up(pp);
    }
    inline void Splay(int x) {
        Update(x);
        for(int p;!Is_Root(x);Rotate(x)) {
            p = par[x];
            if(!Is_Root(p)) Rotate(Get_Child(x) == Get_Child(p) ? p : x);
        }
    }
    inline int Access(int x) {
        int pre = -1;
        while(x != -1) { Splay(x); ch[x][1] = pre; Pull_Up(x); pre = x; x = par[x]; }
        return pre;
    }
    inline void Make_Root(int x) { Access(x); Splay(x); Send(x); }
    inline int Get_Root(int x) {
        Access(x); Splay(x);
        while(ch[x][0] != -1) x = ch[x][0];
        return x;
    }
public:
    inline bool Same_Root(int a ,int b) { return Get_Root(a) == Get_Root(b); }
    inline void Link(int a ,int b) { Make_Root(a); par[a] = b; }
    inline int Max_Route(int a ,int b) { Make_Root(a); return maxi[Access(b)]; }
    inline LCT() {
        memset(ch ,-1 ,sizeof(ch)); memset(par ,-1 ,sizeof(par)); memset(rev ,0 ,sizeof(rev));
        for(int i = 0;i < MAXV;i++) maxi[i] = val[i] = (i >= MAXN ? i - MAXN : -1);
    }
} tree;

struct E { int src ,dst; long long val; } edge[MAXM];
inline bool cmp(E a ,E b) { return a.val < b.val; }

inline void Link(int e) { tree.Link(edge[e].src ,e + MAXN); tree.Link(edge[e].dst ,e + MAXN); }

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int T ,N ,M;
    int i;
    long long sum ,ans ,tmp;
    vector<int> unused;
    for(cin >> T;T--;) {
        cin >> N >> M;
        for(i = 0;i < M;i++) cin >> edge[i].src >> edge[i].dst >> edge[i].val;
        sort(edge ,edge + M ,cmp);
        tree = LCT(); sum = 0; ans = 5e15; unused = vector<int>();
        for(i = 0;i < M;i++) {
            if(tree.Same_Root(edge[i].src ,edge[i].dst)) { unused.push_back(i); }
            else { Link(i); sum += edge[i].val; }
        }
        for(int e : unused) {
            tmp = edge[e].val - edge[tree.Max_Route(edge[e].src ,edge[e].dst)].val;
            ans = min(ans ,sum + tmp);
        }
        cout << sum << " " << ans << '\n';
    }
}
