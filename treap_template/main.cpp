#include <iostream>

#define P 13
int rgen = 1;

using namespace std;
class treap {
    public:
    treap *l ,*r ,*p;
    int key ,elements = 0 ,pri ,value;

    treap(int key ,int value = 0) {
        this->value = value;
        this->key = key;
        this->elements = 1;
        this->pri = rgen;
        rgen = (rgen << 1) % P;
        this->l = this->r = 0;
    }

    treap* merge(treap* tr) {
        if(!tr) return this;
        if(!this) return tr;
        if(this->pri < tr->pri) {
            this->r = this->r->merge(tr);
            this->pull();
            return this;
        } else {
            tr->l = this->merge(tr->l);
            tr->pull();
            return tr;
        }
    }

    void split(int key ,treap*& a, treap*& b) {
        if(!this) {
            a = b = 0;
        } else if(this->key <= key) {
            a = this;
            this->r->split(key ,a->r ,b);
            a->pull() ,b->pull();
        } else if(this->key > key) {
            b = this;
            this->l->split(key ,a ,b->l);
            a->pull() ,b->pull();
        }
    }

    void pull() {
        if(!this) return;
        this->elements = (this->l ? this->l->elements : 0) + (this->r ? this->r->elements : 0) + 1;
    }

    void dfs(int pkey = -1) {
        if(!this) return;
        this->l->dfs(this->key);
        printf("k:%d\tv:%d\tpri:%d\tcount:%d\tpvalue:%d\n" ,this->key ,this->value ,this->pri ,this->elements ,pkey);
        this->r->dfs(this->key);
    }

    treap* kth(int rank) {
        int lcount = (this->l ? this->l->elements : 0);
        if(rank <= lcount) {
            return this->l->kth(rank);
        } else if(lcount + 1 == rank) {
            return this;
        } else {
            return this->r->kth(rank - lcount - 1);
        }
    }
};

inline void insert(treap* root ,int data) {
    treap *a ,*b ;
    root->split(data ,a ,b);
    root = a->merge(new treap(data));
    root = root->merge(b);
}

int main()
{
    int N ,Q;
    int i ,eax ,cmd;
    while(cin >> N) {
        treap *root = new treap(0);
        for(i = 1;i <= N;i++) {
            cin >> eax;
            insert(root ,eax);
        }
        root->dfs();

        for(cin >> Q;Q--;) {
            cin >> cmd;
            if(cmd == 1) {
                cin >> eax;
                printf("The %d-th minimum number is %d\n" ,eax ,root->kth(eax)->key);
            } else {
                cin >> eax;
                printf("Insert %d to the set\n", eax);
                insert(root ,eax);
            }
        }
    }
    return 0;
}
