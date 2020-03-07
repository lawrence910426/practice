#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 2e4 + 50 ,INF = (1LL << 31) - 1;
struct stree { int l ,r ,maxi ,value; } seg[MAXN];
struct st {
    static void Pull_Up(int id) {
        seg[id].maxi = seg[id].value;
        if(seg[id].l != -1) seg[id].maxi = max(seg[id].maxi ,seg[seg[id].l].maxi);
        if(seg[id].r != -1) seg[id].maxi = max(seg[id].maxi ,seg[seg[id].r].maxi);
    }
    static void Modify(int id ,int l ,int r ,int pos ,int val) {
        if(l == r - 1) seg[id].maxi = seg[id].value = val;
        if(l <= pos && pos < r) {
            Modify(seg[id].l ,l ,(l + r) / 2 ,pos ,val);
            Modify(seg[id].r ,(l + r) / 2 ,r ,pos ,val);
        }
    }
    static int Query(int id ,int l ,int r ,int ql ,int qr) {
        if(qr <= l || r <= ql) return -INF;
        if(ql <= l && r <= qr) return seg[id].maxi;
        else return max(Query(seg[id].l ,l ,(l + r) / 2 ,ql ,qr) ,Query(seg[id].r ,l ,r ,ql ,qr));
    }
    static int Build(int &id ,int l ,int r) {
        int self = id++;
        if(l != r - 1) seg[self] = stree{Build(id ,l ,(l + r) / 2) ,Build(id ,(l + r) / 2 ,r) ,-INF ,-INF};
        else seg[self] = stree{-1 ,-1 ,-INF ,-INF};
        return self;
    }
    static int Query(int l ,int r) { return Query(0 ,0 ,MAXN ,l ,r); }
    static void Modify(int pos ,int val) { Modify(0 ,0 ,MAXN ,pos ,val); }
    static void Build() { int id = 0; Build(id ,0 ,MAXN); }
};

struct T {
    vector<int> kids;
    int head ,id ,siz ,dep ,par ,val;
} tree[MAXN];

void preprocess(int pos ,int depth ,int par) {
    tree[pos].siz = 1; tree[pos].dep = depth; tree[pos].par = par;
    for(int V : tree[pos].kids) {
        preprocess(V ,depth + 1);
        tree[pos].siz += tree[V].siz;
    }
}

void Decomp(int pos ,int head ,int& id) {
    tree[pos].id = id; id += 1; tree[pos].head = head;
    st::Modify(tree[pos].id ,tree[pos].val);
    if(tree[pos].kids.size() != 0) {
        int maxi = tree[pos].kids[0];
        for(int V : tree[pos].kids) if(tree[maxi].siz < tree[V].siz) maxi = V;
        Decomp(maxi ,head ,id);
        for(int V : tree[pos].kids) if(V != maxi) Decomp(V ,V ,id);
    }
}

int Query(int a ,int b) {
    int ans = -INF;
    while(tree[a].head != tree[b].head) {
        if(tree[a].dep < tree[b].dep) {
            ans = max(ans ,st::Query(tree[b].id ,tree[tree[b].head].id));
            b = tree[tree[b].head].par;
        } else {
            ans = max(ans ,st::Query(tree[a].id ,tree[tree[a].head].id));
            a = tree[tree[a].head].par;
        }
    }
    ans = max(ans ,st::Query(tree[a].id ,tree[b].id));
    return ans;
}

int T ,N ,a ,b ,v;
int main() {
    int i;
    for(cin >> T;T--;) {
        cin >> N;
        for(i = 0;i < N - 1;i++) {
            cin >> a >> b >> v;
        }
    }
}
