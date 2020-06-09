#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;
const int MAXN = 1e6 + 50;
class LinkCutTree {
    int ch[MAXN][2] ,par[MAXN] ,rev[MAXN];
    long long siz[MAXN] ,vsiz[MAXN];
    bool Is_Root(int x) { return par[x] == -1 || (ch[par[x]][0] != x && ch[par[x]][1] != x); }
    int Get_Child(int x) { return ch[par[x]][1] == x ? 1 : 0; }
    void Send(int x) { swap(ch[x][0] ,ch[x][1]); rev[x] ^= 1; }
    void Push_Down(int x) {
        if(rev[x] == 0) return;
        if(ch[x][0] != -1) Send(ch[x][0]);
        if(ch[x][1] != -1) Send(ch[x][1]);
        rev[x] = 0;
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
        if(!Is_Root(p)) ch[pp][Get_Child(p)] = x;
        par[x] = pp;
        ch[x][style ^ 1] = p;
        par[p] = x;
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
            if(pre != -1) vsiz[x] -= siz[pre];
            if(ch[x][1] != -1) vsiz[x] += siz[ch[x][1]];
            ch[x][1] = pre; Pull_Up(x);
            pre = x; x = par[x];
        }
        return pre;
    }
    void Make_Root(int x) { Access(x); Splay(x); Send(x); }
public:
    LinkCutTree() {
        memset(ch ,-1 ,sizeof(ch)); memset(par ,-1 ,sizeof(par));
        memset(rev ,0 ,sizeof(rev)); memset(vsiz ,0 ,sizeof(vsiz));
        for(int i = 0;i < MAXN;i++) siz[i] = 1;
    }
    void Link(int a ,int b) { Make_Root(a); Make_Root(b); par[a] = b; vsiz[b] += siz[a]; Pull_Up(b); }
    void Cut(int a ,int b) { Make_Root(a); Access(b); Splay(b); ch[b][0] = par[a] = -1; Pull_Up(b); }
    long long Siz(int x) { Make_Root(x); Pull_Up(x); return siz[x]; }
} LCT;

int N ,Q ,x ,y;
char cmd;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q; LCT = LinkCutTree();
    while(Q--) {
        cin >> cmd >> x >> y;
        if(cmd == 'A') LCT.Link(x ,y);
        else {
            LCT.Cut(x ,y);
            cout << LCT.Siz(x) * LCT.Siz(y) << '\n';
            LCT.Link(x ,y);
        }
    }
}
