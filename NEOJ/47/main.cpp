#include <iostream>
#include <random>
#include <cstring>
#pragma GCC optimize("Ofast,no-stack-protector")

using namespace std;
struct treap {
    treap *l ,*r;
    int value ,pri;
    treap(): l(nullptr) ,r(nullptr) ,value(0) ,pri(0) {}
    treap(int val) : l(nullptr) ,r(nullptr) ,value(val) ,pri(rand()) {}
};

treap* merge(treap*& a ,treap*& b) {
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(a->pri < b->pri) {
        a->r = merge(a->r ,b);
        return a;
    } else {
        b->l = merge(a ,b->l);
        return b;
    }
}

// if val exists ,it would be on treap B
void split(treap* t ,int val ,treap*& a ,treap*& b) {
    if(t == nullptr) a = b = nullptr;
    else if(t->value < val) {
        a = t;
        split(t->r ,val ,a->r ,b);
    } else {
        b = t;
        split(t->l ,val ,a ,b->l);
    }
}

int get_min(treap* t) { return (t->l == nullptr ? t->value : get_min(t->l)); }
int get_max(treap* t) { return (t->r == nullptr ? t->value : get_max(t->r)); }

int Q ,v ,L ,R;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    srand(time(NULL));
    string cmd;
    treap *root = nullptr ,*a ,*b ,*c ,*d;
    for(cin >> Q;Q--;) {
        cin >> cmd >> v;
        if(cmd == "insert") {
            split(root ,v ,a ,b);
            c = new treap(v);
            b = merge(c ,b);
            root = merge(a ,b);
        } else if(cmd == "query") {
            split(root ,v ,a ,b);
            split(b ,v + 1 ,c ,d);
            if(c != nullptr) cout << c->value << '\n';
            else if(a == nullptr) cout << get_min(d) << '\n';
            else if(d == nullptr) cout << get_max(a) << '\n';
            else {
                L = get_max(a) ,R = get_min(d);
                if(v - L == R - v) cout << L << " " << R << '\n';
                else if(v - L > R - v) cout << R << '\n';
                else cout << L << '\n';
            }
            b = merge(c ,d);
            root = merge(a ,b);
        } else if(cmd == "delete") {
            split(root ,v ,a ,b);
            split(b ,v + 1 ,c ,d);
            root = merge(a ,d);
        }
    }
}

/*
10
insert 7
insert 8
insert 9
insert 1024
query 8
delete 8
query 8
*/
