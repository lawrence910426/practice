#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;
int N ,K;
struct p {
    int age ,disappoint;
}data[100005];
bool cmp(p a ,p b) { return a.disappoint < b.disappoint; }

struct treap {
    treap *left ,*right;
    long long int value ,pri ,sum ,nodes;
    bool fake;
    treap(): left(nullptr) ,right(nullptr) ,value(0) ,pri(0) ,sum(0) ,nodes(0) ,fake(false) {}
    treap(int v ,bool b): left(nullptr) ,right(nullptr) ,value(v) ,pri(rand()) ,sum(v) ,nodes(1) ,fake(b) {}
}tp[500005];
int used;

void pull(treap*& a) {
    if(a == nullptr) return;
    a->sum = (a->left == nullptr ? 0 : a->left->sum) + (a->right == nullptr ? 0 : a->right->sum) + a->value;
    a->nodes = (a->left == nullptr ? 0 : a->left->nodes) + (a->right == nullptr ? 0 : a->right->nodes) + (a->fake ? 0 : 1);
}

treap* merge(treap *a ,treap *b) {
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(a->pri < b->pri) {
        a->right = merge(a->right ,b);
        pull(a);
        return a;
    } else {
        b->left = merge(a ,b->left);
        pull(b);
        return b;
    }
}

void split(treap *t ,int val ,treap*& a ,treap*& b) {
    if(t == nullptr) {
        a = b = nullptr;
    } else if(t->value < val) {
        a = t;
        split(t->right ,val ,a->right ,b);
        pull(a);
    } else {
        b = t;
        split(t->left ,val ,a ,b->left);
        pull(b);
    }
}

long long int query(treap*& t ,int& need) {
    long long int ans;
    if(t == nullptr) return 0;
    if(t->nodes > need) {
        ans = query(t->right ,need);
        if(need >= 1) {
            need -= 1;
            ans += t->value;
        }
        ans += query(t->left ,need);
    } else {
        ans = t->sum;
        need -= t->nodes;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,need;
    long long int sum ,ans;
    srand(0);
    treap *root ,*a ,*b ,*c;
    while(cin >> N >> K) {
        ans = 0;
        for(i = 0;i < N;i++) cin >> data[i].age >> data[i].disappoint;
        sort(data ,data + N ,cmp);
        used = 0;
        tp[used] = treap(0 ,true);
        root = &tp[used++];
        for(i = N - 1;i >= 0;i--) {
            split(root ,data[i].age ,a ,b);
            tp[used] = treap(data[i].age ,false);
            c = merge(a ,&tp[used++]);
            root = merge(c ,b);
            need = K;
            sum = query(root ,need);
            ans = max(ans ,data[i].disappoint * sum);
        }
        cout << ans << '\n';
    }
}
