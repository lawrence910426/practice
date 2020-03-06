#pragma GCC optimize("Ofast,unroll-loops")
#include <iostream>
#include <memory.h>
#include <algorithm>

const int MAXN = 1e5 + 50;
using namespace std;

int N ,M ,Q;
struct { int x ,y; bool work; } Action[MAXN];
struct { int x ,y ,ans ,limit; } Query[MAXN];
struct link_list { int nxt ,val; } data[MAXN * 30]; int used = 0;

class LinkCutTree {
    int ch[MAXN][2] ,par[MAXN] ,rev[MAXN] ,siz[MAXN] ,vsiz[MAXN];
    inline int Get_Child(int x) { return (ch[par[x]][1] == x ? 1 : 0); }
    inline bool Is_Root(int x) { return par[x] == -1 || (ch[par[x]][0] != x && ch[par[x]][1] != x); }
    inline void Send(int x) { swap(ch[x][0] ,ch[x][1]); rev[x] ^= 1; }
    inline void Push_Down(int x) {
        if(rev[x] != 0) {
            if(ch[x][0] != -1) Send(ch[x][0]);
            if(ch[x][1] != -1) Send(ch[x][1]);
            rev[x] = 0;
        }
    }
    inline void Pull_Up(int x) {
        siz[x] = vsiz[x] + 1;
        if(ch[x][0] != -1) siz[x] += siz[ch[x][0]];
        if(ch[x][1] != -1) siz[x] += siz[ch[x][1]];
    }
    void Update(int x) {
        if(!Is_Root(x)) Update(par[x]);
        Push_Down(x);
    }
    inline void Rotate(int x) {
        int p = par[x] ,pp = par[p] ,style = Get_Child(x) ,subtree = ch[x][style ^ 1];
        par[x] = pp;
        if(!Is_Root(p)) ch[pp][Get_Child(p)] = x;
        par[p] = x;
        ch[x][style ^ 1] = p;
        ch[p][style] = subtree;
        if(subtree != -1) par[subtree] = p;
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
        while(x != -1) {
            Splay(x);
            if(ch[x][1] != -1) vsiz[x] += siz[ch[x][1]];
            if(pre != -1) vsiz[x] -= siz[pre];
            ch[x][1] = pre; Pull_Up(x); pre = x; x = par[x];
        }
        return pre;
    }
    inline void Make_Root(int x) { Access(x); Splay(x); Send(x); }
    inline int Get_Boss(int x) {
        Access(x); Splay(x);
        while(ch[x][0] != -1) x = ch[x][0];
        return x;
    }
public:
    LinkCutTree() {
        memset(ch ,-1 ,sizeof(ch)); memset(par ,-1 ,sizeof(par));
        for(int i = 0;i < MAXN;i++) siz[i] = 1;
        memset(rev ,0 ,sizeof(rev)); memset(vsiz ,0 ,sizeof(vsiz));
    }
    inline void Link(int a ,int b) { Make_Root(a); Make_Root(b); par[a] = b; vsiz[b] += siz[a]; Pull_Up(b); }
    inline void Cut(int a ,int b) { Make_Root(a); Access(b); Splay(b); ch[b][0] = par[a] = -1; Pull_Up(b); }
    inline bool Same(int a ,int b) { return Get_Boss(a) == Get_Boss(b); }
    inline int Size(int x) { Make_Root(x); return siz[x]; }
} LCT;

inline void Move(int src ,int dst) {
    if(src == dst) return;
    if(src < dst) {
        for(int on = src;on != dst;on++) {
            if(LCT.Same(Action[on].x ,Action[on].y)) Action[on].work = false;
            else {
                LCT.Link(Action[on].x ,Action[on].y);
                Action[on].work = true;
            }
        }
    } else {
        for(int on = src;on != dst;on--) if(Action[on].work) LCT.Cut(Action[on].x ,Action[on].y);
    }
}

void Integral_Binary_Search(int l ,int r ,int start) {
    if(start == -1) return;
    if(l == r - 1) {
        for(int iter = start;iter != -1;iter = data[iter].nxt) Query[data[iter].val].ans = l;
    } else {
        int mid = (l + r) / 2 ,siz ,iter ,i;
        int left ,right ,lstart ,rstart;
        left = right = lstart = rstart = -1;
        Move(l ,mid);
        for(iter = start;iter != -1;iter = data[iter].nxt) {
            i = data[iter].val;
            if(LCT.Same(Query[i].x ,Query[i].y)) siz = LCT.Size(Query[i].x);
            else siz = LCT.Size(Query[i].x) + LCT.Size(Query[i].y);
            if(siz < Query[i].limit) {
                if(rstart == -1) rstart = used;
                if(right != -1) data[right].nxt = used;
                data[used] = link_list{-1 ,i};
                right = used;
            } else {
                if(lstart == -1) lstart = used;
                if(left != -1) data[left].nxt = used;
                data[used] = link_list{-1 ,i};
                left = used;
            }
            used += 1;
        }
        Integral_Binary_Search(mid ,r ,rstart);
        Move(mid - 1 ,l - 1);
        Integral_Binary_Search(l ,mid ,lstart);
    }
}

/* use getchar_unlocked for best performance (not supported on windows) */
inline bool gin(int &a){
    char c;
    while(c=getchar(),c<'0'||c>'9')if(c==-1)return 0;
    a=c-'0';
    while(c=getchar(),c>='0'&&c<='9')a=a*10+c-'0';
    return 1;
}

int main() {
    int N ,M ,Q;
    int i;
    gin(N); gin(M);
    for(i = 0;i < M;i++) { gin(Action[i].x); gin(Action[i].y); }
    gin(Q);
    for(i = 0;i < Q;i++) { gin(Query[i].x); gin(Query[i].y); gin(Query[i].limit); }
    for(i = 0;i < Q;i++) { data[used] = link_list{used + 1 ,i}; used += 1; }
    data[used - 1].nxt = -1;
    Integral_Binary_Search(0 ,MAXN ,0);
    for(i = 0;i < Q;i++) cout << Query[i].ans + 1 << '\n';
}
/* This code received TLE. But i dont give a fuck. I used Link-Cut Tree to replace DSU and it worked. */
