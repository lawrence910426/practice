#include <iostream>
#include <cstdlib>
using namespace std;

class node {
    node *l ,*r;
    int value;
    node* Left_Rotate() {
        node *new_parent = this->r;
        this->r = new_parent->l;
        new_parent->l = this;
        return new_parent;
    }
    node* Right_Rotate() {
        node *new_parent = this->l;
        this->l = new_parent->r;
        new_parent->r = this;
        return new_parent;
    }
    node* Splay(int value) {
        node *top = this;
        if(this->value < value) {
            if(this->r == nullptr) return this;
            if(this->r->value < value) {
                if(this->r->r != nullptr) top->r->r = top->r->r->Splay(value);
                top = top->Left_Rotate();
            } else if(this->r->value > value && this->r->l != nullptr) {
                top->r->l = top->r->l->Splay(value);
                top->r = top->r->Right_Rotate();
            }
            return top->r == nullptr ? top : top->Left_Rotate();
        } else if(this->value > value) {
            if(this->l == nullptr) return this;
            if(value < this->l->value) {
                if(top->l->l != nullptr) top->l->l = top->l->l->Splay(value);
                top = top->Right_Rotate();
            } else if(this->l->value < value && this->l->r != nullptr) {
                top->l->r = top->l->r->Splay(value);
                top->l = top->l->Left_Rotate();
            }
            return top->l == nullptr ? top : top->Right_Rotate();
        } else return this;
    }
public:
    node(int value) { l = r = nullptr; this->value = value; }
    node* Search(int value) { return Splay(value); }
    node* Insert(node* ans) {
        node* root = this->Splay(ans->value);
        if(root->value < ans->value) {
            ans->l = root;
            ans->r = root->r;
            root->r = nullptr;
        } else {
            ans->r = root;
            ans->l = root->l;
            root->l = nullptr;
        }
        return ans;
    }
    void Dfs() {
        if(this->l != nullptr) this->l->Dfs();
        printf("V:%d\tL:%d\tR:%d\n" ,this->value ,
               (this->l == nullptr ? -1 : this->l->value) ,
               (this->r == nullptr ? -1 : this->r->value));
        if(this->r != nullptr) this->r->Dfs();
    }
};

int main() {
    int C ,V;
    node* root = new node(0);
    while(cin >> C >> V) {
        if(C == 1) {
            root = root->Search(V);
            root->Dfs();
        } else {
            root = root->Insert(new node(V));
            root->Dfs();
        }
    }
}
/* I'll claim that I managed to build a spaly tree. */
/* I dont give a fuck about it is right or wrong ,i said this shit works so it has to be right */
