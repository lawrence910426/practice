#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

struct treap {
    treap *l ,*r;
    int pri ,value ,nodes;
    treap(int v): l(nullptr) ,r(nullptr) ,pri(rand()) ,value(v) ,nodes(1) {}
    static void pull(treap*& tp) { tp->nodes = 1 + (tp->l == nullptr ? 0 : tp->l->nodes) + (tp->r == nullptr ? 0 : tp->r->nodes); }
    static treap* merge(treap*& a ,treap*& b) {
        if(a == nullptr) return b;
        if(b == nullptr) return a;
        if(a->pri < b->pri) {
            a->r = merge(a->r ,b);
            pull(a);
            return a;
        } else {
            b->l = merge(a ,b->l);
            pull(b);
            return b;
        }
    }
    static void split(treap*& tp ,treap*& a ,treap*& b ,int key) {
        if(tp == nullptr) {
            a = b = nullptr;
        } else if(tp->value >= key) {
            b = tp;
            split(tp->l ,a ,b->l ,key);
        } else {
            a = tp;
            split(tp->r ,a->r ,b ,key);
        }
        if(a != nullptr) pull(a);
        if(b != nullptr) pull(b);
    }
    static treap* query(treap*& tp ,int sum) {
        int lsum = (tp->l == nullptr ? 0 : tp->l->nodes);
        if(lsum + 1 == sum) return tp;
        if(lsum + 1 > sum) return query(tp->l ,sum);
        if(lsum + 1 < sum) return query(tp->r ,sum - lsum - 1);
    }
} data[1e7 + 10];

inline char readchar() {
    static const size_t bufsize = 65536;
    static char buf[bufsize];
    static char *p = buf, *end = buf;
    if (p == end) end = buf + fread(buf, 1, bufsize, stdin), p = buf;
    return *p++;
}

template <class T> void input(T& a) {
    static char p;
    while ((p = readchar()) < '0') ;
    a = p ^ '0';
    while ((p = readchar()) >= '0') a *= 10, a += p ^ '0';
}

int main() {
    srand(time(0));
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int Q ,cmd ,x ,used = 0;
    treap *root  = new treap(0) ,*a ,*b ,*c;
    for(input(Q);Q--;) {
        input(cmd);
        if(cmd == 1) {
            input(x);
            treap::split(root ,a ,c ,x);
            b = new treap(x);
            root = treap::merge(a ,b);
            root = treap::merge(root ,c);
        } else cout << treap::query(root ,(root->nodes) / 2 + 1)->value << '\n';
    }
}
