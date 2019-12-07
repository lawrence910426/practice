#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <vector>
#include <memory.h>
#include <assert.h>
#include <bitset>

using namespace std;
const int MAXN = 1e5 ,root = 0;
vector<int> G[MAXN];
struct node {
    int maxson ,id ,head ,parent;
    vector<int> kids;
} tree[MAXN];
int id ,N ,leaf;

/* ------------------------------------------------------------------------------------ */
long long int zkw[MAXN * 5];
void modify(int pos ,int val) {
    pos += leaf + 1;
    zkw[pos] += val;
    for(pos >>= 1;pos != 1;pos >>= 1) zkw[pos] = zkw[pos * 2] + zkw[pos * 2 + 1];
}
int query(int l ,int r) {
    long long int ans = 0;
    for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
        if(l % 2 == 0) ans += zkw[l ^ 1];
        if(r % 2 == 1) ans += zkw[r ^ 1];
    }
    return ans;
}
/* ------------------------------------------------------------------------------------ */


/* ------------------------------------------------------------------------------------ */
int dfs(int on ,int parent) {
    int nodes = 1 ,son_siz = -1 ,siz;
    tree[on].maxson = -1;
    tree[on].parent = parent;
    for(int V : G[on]) if(V != parent) {
        siz = dfs(V ,on);
        if(siz > son_siz) {
            son_siz = siz;
            tree[on].maxson = V;
        }
        tree[on].kids.push_back(V);
        nodes += siz;
    }
    return nodes;
}

void flatten(int on ,int head) {
    tree[on].id = id++;
    tree[on].head = head;
    if(tree[on].maxson == -1) return;
    flatten(tree[on].maxson ,head);
    for(int V : tree[on].kids) if(V != tree[on].maxson) flatten(V ,V);
}

int operate(int on ,int val) {
    int ans = 0;
    modify(tree[on].id ,val);
    for(;on != -1;on = tree[tree[on].head].parent) ans += query(tree[tree[on].head].id ,tree[on].id + 1);
    return ans;
}
/* ------------------------------------------------------------------------------------ */


/* ------------------------------------------------------------------------------------ */
int main() {
    int Q;
    int i ,src ,dst ,pos ,val;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N) {
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        memset(zkw ,0 ,sizeof(zkw));
        memset(tree ,0 ,sizeof(tree));
        for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
        for(i = 0;i < N - 1;i++) {
            cin >> src >> dst;
            G[src].push_back(dst);
            G[dst].push_back(src);
        }
        id = 0;
        dfs(root ,-1);
        flatten(root ,root);
        for(cin >> Q;Q--;) {
            cin >> pos >> val;
            cout << operate(pos ,val) << '\n';
        }
    }
}
/* ------------------------------------------------------------------------------------ */

/* Fuck you there is a fucking loop on the fucking tree */
