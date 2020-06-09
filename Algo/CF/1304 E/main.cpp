#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;
const int MAXN = 1e5 + 50;
class LinkCutTree {
    int ch[MAXN][2] ,par[MAXN] ,rev[MAXN] ,sum[MAXN];
    inline int Get_Child(int x) { return ch[par[x]][1] == x ? 1 : 0; }
    inline bool Is_Root(int x) { return par[x] == -1 || (ch[par[x]][0] != x && ch[par[x]][1] != x); }
    inline void Pull_Up(int x) {
        sum[x] = 1;
        if(ch[x][0] != -1) sum[x] += sum[ch[x][0]];
        if(ch[x][1] != -1) sum[x] += sum[ch[x][1]];
    }
    inline void Send(int x) { swap(ch[x][0] ,ch[x][1]); rev[x] ^= 1; }
    inline void Push_Down(int x) {
        if(rev[x] == 0) return;
        rev[x] = 0;
        if(ch[x][0] != -1) Send(ch[x][0]);
        if(ch[x][1] != -1) Send(ch[x][1]);
    }
    inline void Update(int x) {
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
        Pull_Up(p) ,Pull_Up(x);
        if(!Is_Root(x)) Pull_Up(pp);
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
public:
    inline LinkCutTree() {
        memset(ch ,-1 ,sizeof(ch)); memset(par ,-1 ,sizeof(par));
        memset(rev ,0 ,sizeof(rev));
        for(int i = 0;i < MAXN;i++) sum[i] = 1;
    }
    inline void Link(int a ,int b) { Make_Root(a); par[a] = b; }
    inline int Length(int a ,int b) { Make_Root(a); return sum[Access(b)]; }
} Tree;

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,Q; cin >> N;
    int i ,a ,b ,x ,y ,K ,temp;
    bool ans;
    for(i = 0;i < N - 1;i++) { cin >> a >> b; Tree.Link(a ,b); }
    for(cin >> Q;Q--;) {
        cin >> x >> y >> a >> b >> K; ans = false;

        temp = Tree.Length(a ,b) - 1;
        if(K >= temp && (K - temp) % 2 == 0) ans = true;

        temp = Tree.Length(a ,x) + Tree.Length(y ,b) - 1;
        if(K >= temp && (K - temp) % 2 == 0) ans = true;

        temp = Tree.Length(a ,y) + Tree.Length(x ,b) - 1;
        if(K >= temp && (K - temp) % 2 == 0) ans = true;

        cout << (ans ? "Yes" : "No") << endl;
    }
}
