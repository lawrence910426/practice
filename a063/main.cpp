#include <iostream>

using namespace std;
#define P 15485867
int rgen = 1;

class treap {
    public:
    int value ,pri ,count;
    bool rev;
    treap *l ,*r;

    treap(int value) {
        this->value = value;
        this->pri = rand();
        rgen <<= 1;
        this->l = this->r = 0;
        this->count = 1;
        this->rev = false;
    }

    static treap* merge(treap* a ,treap* b) {
        if(!a) return b;
        if(!b) return a;
        if(a->pri < b->pri) {
            a->down();
            a->r = treap::merge(a->r ,b);
            a->up();
            return a;
        } else {
            b->down();
            b->l = treap::merge(a ,b->l);
            b->up();
            return b;
        }
    }

    static void split(treap* data ,treap*& a ,treap*& b ,int rank) {
        if(data) {
            data->down();
            int lcount = (data->l ? data->l->count : 0);
            if(rank <= lcount) {
                b = data;
                treap::split(data->l ,a ,b->l ,rank);
            } else {
                a = data;
                treap::split(data->r ,a->r ,b ,rank - lcount - 1);
            }
            data->up();
        } else {
            a = b = 0;
        }
    }

    void up() {
        this->count = 1 + (this->l ? this->l->count : 0) + (this->r ? this->r->count : 0);
    }

    void down() {
        if(this->rev) {
            this->rev = false;
            swap(this->l ,this->r);
            if(this->l) this->l->rev = !this->l->rev;
            if(this->r) this->r->rev = !this->r->rev;
        }
    }

    void dfs(int parent = -1) {
        this->down();
        if(this->l) this->l->dfs(this->value);
        if(this->value != 0) cout << this->value << " ";
        if(this->r) this->r->dfs(this->value);
    }
};



int main() {
    srand(0);
    ios::sync_with_stdio(0), cin.tie(0) ,cout.tie(0);
    int N ,M;
    int i ,L ,R;
    while(cin >> N >> M) {
        treap *a ,*b ,*c ,*d ,*root = new treap(0);
        for(i = 1;i <= N;i++) root = treap::merge(root ,new treap(i));
        while(M--) {
            cin >> L >> R;
            treap::split(root ,a ,b ,L);
            treap::split(b ,c ,d ,R - L + 1);
            c->rev = !c->rev;
            root = treap::merge(a ,treap::merge(c ,d));
        }
        root->dfs();
        cout << '\n';
    }
}
