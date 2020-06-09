#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <memory.h>
#include <bitset>

using namespace std;
const int MAXN = 1e5 + 50, ROOT = 0;
enum Query_Type { Weight, Sum };
int weight_raw[MAXN], weight[MAXN]; bitset<MAXN> color;

class zkw {
public:
    struct { long long weight_sum, weight, lazy_tag ,ans; } node[MAXN * 5];
    int leaf;
    zkw() {
        memset(node, 0, sizeof(node));
        for(leaf = 1;leaf < MAXN + 2;leaf <<= 1) ;
        for(int i = leaf + 1;i < leaf + 1 + MAXN;i++) node[i].weight = node[i].weight_sum = weight[i - leaf - 1];
        for(int i = leaf - 1;i > 0;i--) Pull_Up(i);
    }
    void Pull_Up(int x) {
        node[x].weight_sum = node[x * 2].weight_sum + node[x * 2 + 1].weight_sum + node[x].weight;
        node[x].ans = node[x * 2].ans + node[x * 2 + 1].ans + node[x].weight_sum * node[x].lazy_tag;
    }
    void Modify(int l, int r) {
        for(l += leaf, r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
            if(l % 2 == 0) { node[l ^ 1].lazy_tag += 1; Pull_Up(l ^ 1); }
            if(r % 2 == 1) { node[r ^ 1].lazy_tag += 1; Pull_Up(r ^ 1); }
            Pull_Up(l >> 1); Pull_Up(r >> 1);
        }
        for(l >>= 1;l > 0;l >>= 1) Pull_Up(l);
    }
    long long Query(int l, int r, Query_Type type) {
        long long ans = 0, lsum = 0, rsum = 0;
        for(l += leaf, r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
            if(l % 2 == 0) { ans += node[l ^ 1].ans; lsum += node[l ^ 1].weight_sum; }
            if(r % 2 == 1) { ans += node[r ^ 1].ans; rsum += node[r ^ 1].weight_sum; }
            ans += lsum * node[l >> 1].lazy_tag + rsum * node[r >> 1].lazy_tag;
        }
        for(l >>= 1;l > 0;l >>= 1) ans += (lsum + rsum) * node[l].lazy_tag;
        return type == Query_Type::Sum ? ans : lsum + rsum;
    }
} seg;

class TreeDecomposition {
    struct { int id, par, head, kids; vector<int> kid; } node[MAXN];
    void preprocess(int on, int par) {
        node[on].kids = 1; node[on].par = par;
        for(int V : G[on]) if(V != par) { preprocess(V, on); node[on].kids += node[V].kids; node[on].kid.push_back(V); }
    }
    void chain_decomposition(int on, int head, int& id) {
        int maxi = -1, maxi_kid = -1;
        weight[id] = weight_raw[on]; node[on].id = id; node[on].head = head; id += 1;
        for(int V : node[on].kid) if(node[V].kids > maxi) { maxi = node[V].kids; maxi_kid = V; }
        if(maxi_kid == -1) return;
        chain_decomposition(maxi_kid, head, id);
        for(int V : node[on].kid) if(V != maxi_kid) chain_decomposition(V, V, id);
    }
public:
    vector<int> G[MAXN];
    TreeDecomposition() {  }
    void Decompse() { int id = 0; preprocess(ROOT, -1); chain_decomposition(ROOT, ROOT, id); seg = zkw(); }
    long long query(int on, Query_Type type) {
        long long ans = 0;
        for(int head;on != -1;on = node[head].par) { head = node[on].head; ans += seg.Query(node[head].id, node[on].id + 1, type); }
        return ans;
    }
    void Tag(int on) { for(int head;on != -1;on = node[head].par) { head = node[on].head; seg.Modify(node[head].id, node[on].id + 1); } }
} Tree;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, Q; int i, a, b, cmd, pos; cin >> N >> Q;
    for(i = 1;i < N;i++) { cin >> a >> b >> weight_raw[i]; Tree.G[a].push_back(b); Tree.G[b].push_back(a); }
    long long blacks = 0, points = 0; Tree.Decompse(); color.reset();
    while(Q--) {
        cin >> cmd >> pos;
        if(cmd == 1 && color[pos] == false) { blacks += Tree.query(pos, Query_Type::Weight); points += 1; Tree.Tag(pos); color[pos] = true; }
        if(cmd == 2) { cout << blacks + points * Tree.query(pos, Query_Type::Weight) - 2 * Tree.query(pos, Query_Type::Sum) << '\n'; }
    }
}
