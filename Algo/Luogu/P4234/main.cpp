#pragma GCC optimize("Ofast")

#include <iostream>
#include <algorithm>
#include <set>
#include <memory.h>
#include <assert.h>

using namespace std;

const int MAXN = 5e4 + 50 ,MAXM = 2e5 + 50 ,MAXV = MAXN + MAXM ,INF = (1LL << 31) - 1;
struct E { int src ,dst ,wei; } edge[MAXM];
bool cmp(E a ,E b) { return a.wei < b.wei; }

class LCT {
    int ch[MAXV][2] ,rev[MAXV] ,mini[MAXV] ,par[MAXV] ,val[MAXV];
    bool Is_Root(int x) { return par[x] == -1 || (ch[par[x]][0] != x && ch[par[x]][1] != x); }
    int Get_Child(int x) { return (ch[par[x]][1] == x ? 1 : 0); }
    void Pull_Up(int x) {
        mini[x] = val[x];
        if(ch[x][0] != -1) mini[x] = min(mini[x] ,mini[ch[x][0]]);
        if(ch[x][1] != -1) mini[x] = min(mini[x] ,mini[ch[x][1]]);
    }
    void Push_Down(int x) {
        if(rev[x] != 0) {
            swap(ch[x][0] ,ch[x][1]);
            if(ch[x][0] != -1) rev[ch[x][0]] ^= 1 ,Push_Down(ch[x][0]);
            if(ch[x][1] != -1) rev[ch[x][1]] ^= 1 ,Push_Down(ch[x][1]);
            rev[x] = 0;
        }
    }
    void Rotate(int x) {
        int p = par[x] ,pp = par[par[x]] ,style = Get_Child(x) ,subtree = ch[x][style ^ 1];
        par[x] = pp;
        if(!Is_Root(p)) ch[pp][Get_Child(p)] = x;
        ch[p][style] = subtree;
        if(subtree != -1) par[subtree] = p;
        ch[x][style ^ 1] = p;
        par[p] = x;
        Pull_Up(x);
        Pull_Up(p);
        if(!Is_Root(p)) Pull_Up(pp);
    }
    void Update(int x) {
        if(!Is_Root(x)) Update(par[x]);
        Push_Down(x);
    }
    void Splay(int x) {
        Update(x);
        for(int p = par[x];!Is_Root(x);Rotate(x)) {
            p = par[x];
            if(!Is_Root(p)) Rotate(Get_Child(p) == Get_Child(x) ? p : x);
        }
    }
    int Access(int x) {
        int pre = -1;
        while(x != -1) {
            Splay(x);
            ch[x][1] = pre;
            Pull_Up(x);
            pre = x;
            x = par[x];
        }
        return pre;
    }
    void Make_Root(int x) {
        Access(x);
        Splay(x);
        rev[x] ^= 1;
        Push_Down(x);
    }
public:
    inline int Get_Boss(int x) {
        for(x = Access(x);ch[x][0] != -1;x = ch[x][0]) ;
        return x;
    }
    void Link(int a ,int b) { Make_Root(a); par[a] = b; }
    void Cut(int a ,int b) { Make_Root(a); Access(b); Splay(b); ch[b][0] = par[a] = -1; Pull_Up(b); }
    int Find_Min(int a ,int b) {
        Make_Root(a);
        int root = Access(b);
        Splay(root);
        return mini[root];
    }
    LCT() {
        memset(ch ,-1 ,sizeof(ch)); memset(par ,-1 ,sizeof(par)); memset(rev ,0 ,sizeof(rev));
        for(int i = 0;i < MAXV;i++) val[i] = mini[i] = (i >= MAXN ? i - MAXN : INF);
    }
} tree;

void Cut(int e) { tree.Cut(edge[e].src ,e + MAXN); tree.Cut(edge[e].dst ,e + MAXN); }
void Link(int e) { tree.Link(edge[e].src ,e + MAXN); tree.Link(edge[e].dst ,e + MAXN); }

int main() {
    main();
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,M ,ans = INF ,mini;
    int i ,lptr ,rptr;

    cin >> N >> M;
    for(i = 0;i < M;i++) cin >> edge[i].src >> edge[i].dst >> edge[i].wei;
    sort(edge ,edge + M ,cmp);
    tree = LCT();
    for(i = 0;i < M;i++) Link(i);
    for(i = 0;i < M;i++) Cut(i);
    /* for(lptr = rptr = 0;lptr < M;lptr++) {
        while(!codes.empty() && *codes.begin() < lptr) {
            Cut(mini = tree.Find_Min(edge[*codes.begin()].src ,edge[*codes.begin()].dst));
            codes.erase(mini);
        }
        for(;rptr < M && codes.size() < N - 1;rptr++) {
            if(tree.Get_Boss(edge[rptr].src) == tree.Get_Boss(edge[rptr].dst)) {
                Cut(mini = tree.Find_Min(edge[rptr].src ,edge[rptr].dst));
                codes.erase(mini);
            }
            Link(rptr);
            codes.insert(rptr);
        }
        if(!codes.empty() && codes.size() == N - 1) ans = min(ans ,edge[*codes.rbegin()].wei - edge[*codes.begin()].wei);
    } */
    cout << ans << '\n';
}
