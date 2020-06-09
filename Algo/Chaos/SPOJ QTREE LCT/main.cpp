#include <iostream>
#include <algorithm>
#include <memory.h>
#include <map>
#include <cstring>

using namespace std;
const int MAXN = 3e4 + 50 ,INF = (1LL << 31) - 1 ,AUX = 1e4 + 50;
class Link_Cut_Tree {
    int ch[MAXN][2] ,par[MAXN] ,rev[MAXN] ,maxi[MAXN] ,val[MAXN];
    bool Is_Root(int x) { return par[x] == -1 || (ch[par[x]][0] != x && ch[par[x]][1] != x); }
    int Get_Child(int x) { return (ch[par[x]][1] == x ? 1 : 0); }
    void Send(int x) { swap(ch[x][0] ,ch[x][1]); rev[x] ^= 1; }
    void Push_Down(int x) {
        if(rev[x] == 0) return;
        if(ch[x][0] != -1) Send(ch[x][0]);
        if(ch[x][1] != -1) Send(ch[x][1]);
        rev[x] = 0;
    }
    void Pull_Up(int x) {
        maxi[x] = val[x];
        if(ch[x][0] != -1) maxi[x] = max(maxi[x] ,maxi[ch[x][0]]);
        if(ch[x][1] != -1) maxi[x] = max(maxi[x] ,maxi[ch[x][1]]);
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
            ch[x][1] = pre;
            Pull_Up(x);
            pre = x;
            x = par[x];
        }
        return pre;
    }
    void Make_Root(int x) { Access(x); Splay(x); Send(x); }
public:
    Link_Cut_Tree() {
        memset(ch ,-1 ,sizeof(ch)); memset(par ,-1 ,sizeof(par)); memset(rev ,0 ,sizeof(rev));
        for(int i = 0;i < MAXN;i++) val[i] = maxi[i] = -INF;
    }
    void Link(int a ,int b) { Make_Root(a); par[a] = b; }
    int Get(int a ,int b) { Make_Root(a); return maxi[Access(b)]; }
    void Modify(int x ,int value) { Make_Root(x); val[x] = value; Pull_Up(x); }
} LCT;

int Aux = 1e4 + 50;
int E[MAXN];
void Link(int a ,int b ,int id ,int value) {
    E[id] = Aux;
    LCT.Link(a ,Aux); LCT.Link(b ,Aux);
    LCT.Modify(Aux ,value);
    Aux += 1;
}

void Modify(int id ,int value) { LCT.Modify(E[id] ,value); }

int T ,N;
int main() {
    int i ,a ,b ,id ,val;
    string cmd;
    ios::sync_with_stdio(0); cin.tie(0);
    for(cin >> T;T--;) {
        cin >> N; Aux = AUX; LCT = Link_Cut_Tree();
        for(i = 0;i < N - 1;i++) {
            cin >> a >> b >> val;
            Link(a ,b ,i + 1 ,val);
        }
        while(cin >> cmd) {
            if(cmd == "DONE") break;
            if(cmd == "QUERY") {
                cin >> a >> b;
                cout << LCT.Get(a ,b) << '\n';
            }
            if(cmd == "CHANGE") {
                cin >> id >> val;
                Modify(id ,val);
            }
        }
    }
}
