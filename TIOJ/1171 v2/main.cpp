#include <iostream>

using namespace std;
const int MAXN = 1e5 + 50, ROOT = 0;
long long weight[MAXN]; int edge[MAXN][2];
class LinkCutTree {
    struct {
        int kid[2], par, rev;
        long long tag, weight, lazy_tag, weight_sum, ans;
    } node[MAXN];
    void Pull(int p, int x) {
        node[p].ans += node[x].ans;
        node[p].weight_sum += node[x].weight_sum;
    }
    void Pull_Up(int x) {
        node[x].ans = 0; node[x].weight_sum = node[x].weight;
        if(node[x].kid[0] != -1) Pull(x, node[x].kid[0]);
        if(node[x].kid[1] != -1) Pull(x, node[x].kid[1]);
        node[x].ans += node[x].tag * node[x].weight + node[x].lazy_tag * node[x].weight_sum;
    }
    void Push(int p, int x) {
        if(node[p].rev != 0) swap(node[x].kid[0], node[x].kid[1]);
        if(node[p].lazy_tag != 0) {
            node[x].lazy_tag += node[p].lazy_tag;
            Pull_Up(x);
        }
    }
    void Push_Down(int x) {
        if(node[x].kid[0] != -1) Push(x, node[x].kid[0]);
        if(node[x].kid[1] != -1) Push(x, node[x].kid[1]);
        node[x].rev = 0; node[x].tag += node[x].lazy_tag; node[x].lazy_tag = 0;
    }
    bool Is_Root(int x) { return (node[x].par == -1 || (node[node[x].par].kid[0] != x && node[node[x].par].kid[1] != x)); }
    int Get_Child(int x) { return (node[node[x].par].kid[0] == x ? 0 : 1); }
    void Update(int x) {
        if(!Is_Root(x)) Update(node[x].par);
        Push_Down(x);
    }
    void Rotate(int x) {
        int p = node[x].par, pp = node[p].par, style = Get_Child(x), subtree = node[x].kid[style ^ 1];
        if(!Is_Root(p)) node[pp].kid[Get_Child(p)] = x;
        node[x].par = pp;
        node[x].kid[style ^ 1] = p;
        node[p].par = x;
        node[p].kid[style] = subtree;
        if(subtree != -1) node[subtree].par = p;
        Pull_Up(p); Pull_Up(x);
        if(!Is_Root(x)) Pull_Up(pp);
    }
    void Splay(int x) {
        Update(x);
        for(int p;!Is_Root(x);Rotate(x)) {
            p = node[x].par;
            if(!Is_Root(p)) Rotate(Get_Child(x) == Get_Child(p) ? p : x);
        }
    }
    void Access(int x) {
        for(int p = -1;x != -1;x = node[x].par) {
            Splay(x);
            node[x].kid[1] = p;
            Pull_Up(x);
            p = x;
        }
    }
    void Make_Root(int x) { Access(x); Splay(x); node[x].rev ^= 1; swap(node[x].kid[0], node[x].kid[1]); }
public:
    LinkCutTree() {
        for(int i = 0;i < MAXN;i++) {
            node[i].kid[0] = node[i].kid[1] = node[i].par = -1; node[i].rev = 0;
            node[i].weight = node[i].weight_sum = weight[i]; node[i].tag = node[i].ans = 0;
        }
    }
    void Link(int a, int b) { Make_Root(a); node[a].par = b; }
    void Tag(int a, int b) {
        Make_Root(a); Access(b); Splay(b); node[b].lazy_tag += 1;
        Pull_Up(b);
    }
    long long Sum(int a, int b) { Make_Root(a); Access(b); Splay(b); return node[b].ans; }
} LCT;
int main() {
    int N, Q, cmd ,pos; cin >> N >> Q;
    for(int i = 1;i < N;i++) cin >> edge[i][0] >> edge[i][1] >> weight[i];
    LCT = LinkCutTree();
    for(int i = 1;i < N;i++) LCT.Link(edge[i][0], edge[i][1]);
    while(Q--) {
        cin >> cmd >> pos;
        if(cmd == 1) LCT.Tag(pos, ROOT);
        if(cmd == 2) cout << LCT.Sum(pos, ROOT) << endl;
    }
}
