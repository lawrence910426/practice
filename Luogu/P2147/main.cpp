#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 50;

class node {
    bool rev;

    inline int get_child() { return par->ch[1] == this ? 1 : 0; }
    inline bool is_root() { return par == nullptr || (par->ch[0] != this && par->ch[1] != this);}
    inline void push_down() {
        if(rev) {
            swap(ch[0] ,ch[1]);
            if(ch[0] != nullptr) ch[0]->rev = !ch[0]->rev;
            if(ch[1] != nullptr) ch[1]->rev = !ch[1]->rev;
            rev = false;
        }
    }
    void update() {
        if(!is_root()) par->update();
        push_down();
    }
    void rotation() {
        node *p = par ,*pp = par->par;
        int style = this->get_child();
        this->par = pp;
        if(!p->is_root()) pp->ch[p->get_child()] = this;
        p->ch[style] = this->ch[style ^ 1];
        if(this->ch[style ^ 1] != nullptr) this->ch[style ^ 1]->par = p;
        this->ch[style ^ 1] = p;
        p->par = this;
    }
public:
    node *ch[2] ,*par;
    node() { ch[0] = ch[1] = par = nullptr; rev = false; }
    void splay() {
        this->update();
        for(node *p = this->par;!this->is_root();this->rotation()) {
            if(!p->is_root()) {
                if(p->get_child() == this->get_child()) p->rotation();
                else this->rotation();
            }
            p = this->par;
        }
    }
    node* access() {
        node *pre = nullptr ,*pos = this;
        while(pos != nullptr) {
            pos->splay();
            pos->ch[1] = pre;
            pre = pos;
            pos = pos->par;
        }
        return pre;
    }
    void make_root() {
        node* root = this->access();
        root->rev = !root->rev;
        swap(root->ch[0] ,root->ch[1]);
    }
    node* get_root() {
        node* root = access();
        root->splay();
        while(root->ch[0] != nullptr) {
            root->push_down();
            root = root->ch[0];
        }
        return root;
    }
} *tree[MAXN];

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,Q ,a ,b;
    string cmd;
    while(cin >> N >> Q) {
        for(int i = 0;i < MAXN;i++) tree[i] = new node();
        while(Q--) {
            cin >> cmd >> a >> b;
            if(cmd == "Connect") {
                if(tree[a]->get_root() == tree[b]->get_root()) continue;
                tree[a]->make_root();
                tree[a]->par = tree[b];
            } else if(cmd == "Query") {
                cout << (tree[a]->get_root() == tree[b]->get_root() ? "Yes" : "No") << endl;
            } else if(cmd == "Destroy") {
                tree[a]->make_root();
                tree[b]->access();
                tree[b]->splay();
                if(tree[a]->par == tree[b] && tree[b]->ch[0] == tree[a] && tree[a]->ch[1] == nullptr)
                    tree[b]->ch[0] = tree[a]->par = nullptr;
            } else return -1;
        }
    }
}
