#include <iostream>
#include <memory.h>
#include <random>
#include <time.h>

using namespace std;
const int MAXN = 1e5 + 50 ,INF = (1LL << 31) - 1;
int data[MAXN];
struct treap {
    treap *l ,*r;
    int value ,pri ,close;
    treap(int v): value(v) ,pri(rand()) ,l(nullptr) ,r(nullptr) {}
    treap(treap* t): l(t->l) ,r(t->r) ,value(t->value) ,pri(t->pri) {}
    ~treap() { if(l != nullptr) delete l; if(r != nullptr) delete r; }
    static void pull(treap* t) {
        t->close = min(t->l == nullptr ? INF : t->l->close ,t->r == nullptr ? INF : t->r->close);
        t->close = min(t->l == nullptr ? INF : t->value - t->l->value ,t->r == nullptr ? INF : t->r->value - t->value);
    }
    static treap* merge(treap* l ,treap* r) {
        if(l == nullptr) return r;
        if(r == nullptr) return l;
        if(l->pri < r->pri) {
            l->r = merge(l->r ,r);
            pull(l);
            return l;
        } else {
            r->l = merge(l ,r->l);
            pull(r);
            return r;
        }
    }
    static void split(treap* t ,treap*& a ,treap*& b ,int key) {
        if(t == nullptr) a = b = nullptr;
        else if(t->value <= key) {
            b = t;
            split(t->l ,a ,b->l ,key);
            pull(b);
        } else if(key < t->value) {
            a = t;
            split(t->r ,a->r ,b ,key);
            pull(a);
        }
    }
    static treap* join(treap* a ,treap* b) {
        treap *la ,*ra;
        split(a ,la ,ra ,b->value);
        return merge(merge(la ,b) ,ra);
    }
};
struct zkw {
    int seg[MAXN * 5] ,leaf;
    zkw(int N) {
        int i;
        memset(seg ,0 ,sizeof(seg));
        for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
        for(i = 0;i < N;i++) seg[i + leaf + 1] = new treap(data[i]);
        for(i = leaf - 1;i >= 0;i--) seg[i] =
    }
};
int main() {
}
