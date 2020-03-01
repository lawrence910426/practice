///#pragma GCC optimize("Ofast")
#include <iostream>
#include <memory.h>
#include <set>
#include <memory>

using namespace std;
const int MAXN = 1e5 + 50;

class Node {
    shared_ptr<Node> l ,r;
    int val ,sum;
    Node(shared_ptr<Node> L ,shared_ptr<Node> R ,int V ,int S) { l = L; r = R; val = V; sum = S; }
    Node* Pull_Up() {
        this->sum = this->val;
        if(this->l != nullptr) this->sum += this->l->sum;
        if(this->r != nullptr) this->sum += this->r->sum;
    }
    shared_ptr<Node> Build(int l ,int r) {
        if(l == r - 1) return shared_ptr<Node>(new Node(nullptr ,nullptr ,0 ,0));
        else return shared_ptr<Node>(new Node(Build(l ,(l + r) / 2) ,Build((l + r) / 2 ,r) ,0 ,0));
    }
    shared_ptr<Node> Modify(int l ,int r ,int pos ,int diff) {
        shared_ptr<Node> ret = shared_ptr<Node>(new Node(*this));
        if(l == r - 1) ret->val += diff;
        else {
            int mid = (l + r) / 2;
            if(pos < mid) ret->l = this->l->Modify(l ,mid ,pos ,diff);
            else ret->r = this->r->Modify(mid ,r ,pos ,diff);
        }
        ret->Pull_Up();
        return ret;
    }
    int Query(int l ,int r ,int ql ,int qr) {
        if(qr <= l || r <= ql) return 0;
        if(ql <= l && r <= qr) return this->sum;
        else return this->l->Query(l ,(l + r) / 2 ,ql ,qr) + this->r->Query((l + r) / 2 ,r ,ql ,qr);
    }
public:
    int N;
    Node() {}
    ~Node() {}
    Node(int siz) { N = siz; this->Build(0 ,N); }
    void Modify(int pos ,int diff) { this->Modify(0 ,N ,pos ,diff); }
    int Query(int l ,int r) { return this->Query(0 ,N ,l ,r); }
};

class Seg {
    int N ,leaf;
    Node *data[MAXN * 3];
public:
    Seg() {}
    inline Seg(int siz):N(siz) {
        for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
        data[1] = new Node(N + 1);
        for(int i = 2;i < leaf * 2;i++) data[i] = data[i - 1];
    }
    inline void Modify(int pos ,int index ,int diff) { for(pos += leaf + 1;pos >= 1;pos >>= 1) data[pos]->Modify(index ,diff); }
    inline int Query(int l ,int r ,int ll ,int rr) {
        int ans = 0;
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(l % 2 == 0) ans += data[l ^ 1]->Query(ll ,rr);
            if(r % 2 == 1) ans += data[r ^ 1]->Query(ll ,rr);
        }
        return ans;
    }
} seg ,fix;

class Fenwick {
    int data[MAXN];
    inline int lowbit(int x) { return x & (-x); }
    inline void Q(int pos ,int& ans) { for(ans = 0;pos > 0;pos -= lowbit(pos)) ans += data[pos]; }
public:
    inline int Query(int l ,int r) { int la ,ra; Q(l + 1 ,la); Q(r + 1 ,ra); return ra - la; }
    inline void Modify(int pos ,int val) { for(pos += 2;pos < MAXN;pos += lowbit(pos)) data[pos] += val; }
    inline Fenwick() { memset(data ,0 ,sizeof(data)); }
} BIT;
/* Every data structure above uses left-closed right-opened segment and zero-based codec as input interface. */

set<int> Barrier[MAXN];
int raw[MAXN];
struct { int R ,V; } Laser[MAXN];

void Modify(int pos ,int x) {
    int old = raw[pos] ,nxt ,pre; set<int>::iterator it;
    BIT.Modify(pos ,-old);
    Barrier[old].erase(pos);
    it = Barrier[old].lower_bound(pos);
    nxt = (pos > *Barrier[old].rbegin() ? -1 : *it);
    pre = (it == Barrier[old].begin() ? -1 : *prev(it));
    if(pre != -1) fix.Modify(pre ,pos ,-raw[pre]);
    if(nxt != -1) fix.Modify(pos ,nxt ,-old);
    if(pre != -1 && nxt != -1) fix.Modify(pre ,nxt ,raw[pre]);

    raw[pos] = x;
    BIT.Modify(pos ,raw[pos]);
    it = Barrier[x].lower_bound(pos);
    nxt = (pos > *Barrier[x].rbegin() ? -1 : *it);
    pre = (it == Barrier[x].begin() ? -1 : *prev(it));
    if(pre != -1) fix.Modify(pre ,pos ,raw[pre]);
    if(nxt != -1) fix.Modify(pos ,nxt ,raw[pos]);
    if(pre != -1 && nxt != -1) fix.Modify(pre ,nxt ,-raw[pre]);
    Barrier[x].insert(pos);
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,Q ,cmd ,p ,v ,L ,R; cin >> N >> Q;
    int i ,temp;
    seg = Seg(N); memset(Laser ,-1 ,sizeof(Laser));
    fix = Seg(N); memset(raw ,0 ,sizeof(raw));
    for(i = 0;i <= N;i++) Barrier[i].insert(-1);
    for(i = 0;i < N;i++) { cin >> temp; Modify(i ,temp); }
    while(Q--) {
        cin >> cmd;
        if(cmd == 1) {
            cin >> p >> v; p -= 1;
            Modify(p ,v);
        } else if(cmd == 2) {
            cin >> L >> R >> v; L -= 1;
            seg.Modify(L ,R ,v);
            Laser[L].R = R;
            Laser[L].V = v;
        } else if(cmd == 3) {
            cin >> L; L -= 1;
            seg.Modify(L ,Laser[L].R ,-Laser[L].V);
            Laser[L].R = Laser[L].V = -1;
        } else if(cmd == 4) {
            cin >> L >> R; L -= 1;
            cout << seg.Query(L ,R ,L ,R + 1) + BIT.Query(L ,R) - fix.Query(L ,R ,L ,R) << '\n';
        }
    }
}
