#pragma GCC optimize("Ofast")
#include <iostream>
#include <random>
#include <assert.h>

using namespace std;
const int MAXN = 1e5 + 50;

class treap {
    treap *l ,*r, *par;
    int pri;
    void pull_up() { this->siz = 1 + (this->l == nullptr ? 0 : this->l->siz) + (this->r == nullptr ? 0 : this->r->siz); }
    static treap* merge(treap* l, treap *r) {
        if(l == nullptr) return r;
        if(r == nullptr) return l;
        if(l->pri < r->pri) {
            l->r = merge(l->r, r);
            l->pull_up();
            return l;
        } else {
            r->l = merge(l, r->l);
            r->pull_up();
            return r;
        }
    }
    static void split(treap* self, treap*& l, treap*& r, int key) {
        if(self == nullptr) l = r = nullptr;
        else {
            if(self->val < key) {
                l = self;
                split(self->r, l->r, r, key);
                l->pull_up(); 
            } else {
                r = self;
                split(self->l, l, r->l, key);
                r->pull_up();
            }
        }
    }

    static treap* insert(treap* self, treap* item) {
        treap *left = nullptr, *right = nullptr;
        split(self, left, right, item->val);
        return merge(left, merge(item, right));
    }

public: 
    int siz, val;
    treap() {}
    treap(int v): l(nullptr), r(nullptr), pri(rand()), val(v), siz(1) {}
    
    static void dfs(treap* self) {
        if(self == nullptr) return;
        dfs(self->l);
        cout << self->val << " " << self->siz << " " << self->pri << endl;
        dfs(self->r);
    }

    /* Assume that minor->siz < major->siz */
    static treap* meld(treap* minor, treap* major) {
        if(minor == nullptr) return major;
        major = meld(minor->l, major);
        major = meld(minor->r, major);
        minor->l = minor->r = nullptr; minor->pull_up();
        return insert(major, minor);
    }

    static treap* kth(treap* self, int k) {
        int lsiz = (self->l == nullptr ? 0 : self->l->siz);
        if(lsiz >= k) return kth(self->l, k);
        if(lsiz + 1 == k) return self;
        if(lsiz + 1 < k) return kth(self->r, k - lsiz - 1);
    }

    static treap* modify(treap* root, int old, int val) {
        treap *left, *mid, *right, *temp;
        split(root, left, temp, old);
        split(temp, mid, right, old + 1);
        assert(mid->siz == 1);
        mid->val = val;
        return insert(merge(left, right) ,mid);
    }
} storage[MAXN];
treap* root[MAXN];

class DisJointSet {
    int parent[MAXN];
public:
    DisJointSet() { for(int i = 0;i < MAXN;i++) parent[i] = i; }
    int query(int i) { return (i == parent[i] ? i : parent[i] = query(parent[i])); }
    void join(int a, int b) { parent[query(a)] = b; }
} DSU;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, M;
    int i, temp, x, y;
    char cmd;
    cin >> N >> M;
    for(i = 1;i <= N;i++) { cin >> temp; storage[i] = treap(temp); root[i] = &storage[i]; }
    while(M--) {
        cin >> cmd >> x >> y;
        if(cmd == 'A') {
            x = DSU.query(x); y = DSU.query(y);
            if(x == y) continue;
            if(root[x]->siz > root[y]->siz) swap(x, y);
            root[y] = treap::meld(root[x], root[y]);
            DSU.join(x, y);
        } else if(cmd == 'M') {
            treap::modify(root[DSU.query(x)], root[x]->val, y);
        } else if(cmd == 'Q') {
            x = DSU.query(x);
            cout << treap::kth(root[x], root[x]->siz - y + 1)->val << '\n';
        }
    }
}