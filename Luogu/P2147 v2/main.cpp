#include <iostream>
#include <cstring>

using namespace std;
const int MAXN = 1e5 + 50;
struct LCT {
    int ch[MAXN][2] ,tag[MAXN] ,par[MAXN];
    int Get_Child(int t) { return (ch[par[t]][1] == t ? 1 : 0); }
    bool Is_Root(int t) { return par[t] == -1 || (ch[par[t]][0] != t && ch[par[t]][1] != t); }
    void Push_Down(int t) {
        if(tag[t] != 0) {
            swap(ch[t][0] ,ch[t][1]);
            if(tag[ch[t][0]] != -1) tag[ch[t][0]] ^= 1;
            if(tag[ch[t][1]] != -1) tag[ch[t][1]] ^= 1;
            tag[t] = 0;
        }
    }
    void Rotate(int t) {
        int p = par[t] ,pp = par[par[t]] ,style = Get_Child(t) ,subtree = ch[t][style ^ 1];
        if(pp != -1) ch[pp][Get_Child(p)] = t;
        par[t] = pp;
        ch[p][style] = subtree;
        if(subtree != -1) par[subtree] = p;
        ch[t][style ^ 1] = p;
        par[p] = t;
    }
    void Update(int t) {
        if(!Is_Root(t)) Update(par[t]);
        Push_Down(t);
    }
    void Splay(int t) {
        Update(t);
        for(int p = par[t];p != -1;Rotate(t)) {
            if(Get_Child(t) == Get_Child(p)) Rotate(p);
            else Rotate(t);
        }
    }
    int Access(int t) {
        int pre = 0;
        while(t != -1) {
            Splay(t);
            ch[t][1] = pre;
            pre = t;
            t = par[t];
        }
        return pre;
    }
    int Get_Root(int t) {
        for(t = Access(t);ch[t][0] != -1;t = ch[t][0]) ;
        return t;
    }
    void Make_Root(int t) {
        Access(t);
        Splay(t);
        tag[t] ^= 1;
        swap(ch[t][0] ,ch[t][1]);
    }
    LCT() {
        memset(ch ,-1 ,sizeof(ch));
        memset(par ,-1 ,sizeof(par));
        memset(tag ,0 ,sizeof(tag));
    }
} tree;

int main() {
    //ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,Q ,a ,b;
    string cmd;
    while(cin >> N >> Q) {
        tree = LCT();
        while(Q--) {
            cin >> cmd >> a >> b;
            if(cmd == "Connect") {
                if(tree.Get_Root(a) != tree.Get_Root(b)) {
                    tree.Make_Root(a);
                    tree.par[a] = b;
                }
            } else if(cmd == "Destroy") {
                tree.Make_Root(a);
                tree.Access(b);
                tree.Splay(b);
                if(tree.ch[b][0] == a && tree.par[a] == 0 && tree.ch[a][1] == -1) tree.ch[b][0] = tree.par[a] = -1;
            } else if(cmd == "Query") {
                cout << (tree.Get_Root(a) == tree.Get_Root(b) ? "Yes" : "No") << endl;
            } else return -1;
        }
    }
}
