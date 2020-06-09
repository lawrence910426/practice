#include <iostream>
#include <memory.h>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 50;
using namespace std;

int N ,M ,Q;
struct { int x ,y; bool work; } Action[MAXN];
struct { int x ,y ,ans; } Query[MAXN];

class LinkCutTree {
    int ch[MAXN][2] ,par[MAXN] ,rev[MAXN] ,siz[MAXN] ,vsiz[MAXN];
    int Get_Child(int x) { return (ch[par[x]][1] == x ? 1 : 0); }
    bool Is_Root(int x) { return par[x] == -1 || (ch[par[x]][0] != x && ch[par[x]][1] != x); }
    void Send(int x) { swap(ch[x][0] ,ch[x][1]); rev[x] ^= 1; }
    void Push_Down(int x) {
        if(rev[x] != 0) {
            if(ch[x][0] != -1) Send(ch[x][0]);
            if(ch[x][1] != -1) Send(ch[x][0]);
            rev[x] = 0;
        }
    }
    void Pull_Up(int x) {
        siz[x] = vsiz[x] + 1;
        if(ch[x][0] != -1) siz[x] += siz[ch[x][0]];
        if(ch[x][1] != -1) siz[x] += siz[ch[x][1]];
    }
    void Update(int x) {
        if(!Is_Root(x)) Update(par[x]);
        Push_Down(x);
    }
    void Rotate(int x) {
        int p = par[x] ,pp = par[p] ,style = Get_Child(x) ,subtree = ch[x][style ^ 1];
        par[x] = pp;
        if(!Is_Root(pp)) ch[pp][Get_Child(p)] = x;
        par[p] = x;
        ch[x][style ^ 1] = p;
        ch[p][style] = subtree;
        if(subtree != -1) par[subtree] = p;
        Pull_Up(p); Pull_Up(x);
        if(pp != -1) Pull_Up(pp);
    }
    void Splay(int x) {
        Update(x);
        for(int p;!Is_Root(x);Rotate(x)) {
            p = par[x];
            if(!Is_Root(p)) Rotate(Get_Child(x) == Get_Child(p) ? p : x);
        }
    }
    int Access(int x) {
        int pre = -1;
        while(x != -1) {
            Splay(x);
            if(ch[x][1] != -1) vsiz[x] += siz[ch[x][1]];
            if(pre != -1) vsiz[x] -= siz[pre];
            ch[x][1] = pre; Pull_Up(x); pre = x; x = par[x];
        }
        return pre;
    }
    void Make_Root(int x) { Access(x); Splay(x); Send(x); }
    int Get_Boss(int x) {
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
    void Link(int a ,int b) { Make_Root(a); par[a] = b; vsiz[b] += siz[a]; Pull_Up(b); }
    void Cut(int a ,int b) { Make_Root(a); Access(b); Splay(b); ch[b][0] = -1; par[a] = -1; Pull_Up(b); }
    bool Same(int a ,int b) { return Get_Boss(a) == Get_Boss(b); }
    int Size(int x) { Make_Root(x); return siz[x]; }
} LCT;

void Integral_Binary_Search(int l ,int r ,vector<int>& test) {
    if(l == r - 1) {
        for(int i : test) Query[i].ans = l;
    } else {

    }
}

int main() {
    int Q ,x ,y;
    while(cin >> Q) {
        if(Q == 1) {
            cin >> x >> y;
            LCT.Link(x ,y);
        } else if(Q == 2) {
            cin >> x >> y;
            LCT.Cut(x ,y);
        } else if(Q == 3) {
            cin >> x;
            cout << "Ans: " << LCT.Size(x) << endl;
        } else if(Q == 4) {
            cin >> x >> y;
            cout << (LCT.Same(x ,y) ? "Yes" : "No") << endl;
        }
    }

}
/*
1 1 2
1 1 3
1 4 5
3 5
1 3 4
4 5 1

3 1
3 2
3 3
3 4
3 5
2 3 4
4 3 2
*/
