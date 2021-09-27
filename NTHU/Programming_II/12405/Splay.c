#include <stdio.h>
#include <cstdlib>

struct SplayTree {
    struct Node { Node *kid[2], *par; int key; void *val; } *Root = NULL;
    int Get_Child(Node* ptr) { return ptr->par->kid[0] == ptr ? 0 : 1; }
    void Rotate(Node* x) {
        int style = Get_Child(x);
        Node *p = x->par, *pp = p->par, *kid = x->kid[style ^ 1];
        x->par = pp;
        if(pp != NULL) pp->kid[Get_Child(p)] = x;
        p->par = x;
        x->kid[style ^ 1] = p;
        p->kid[style] = kid;
        if(kid != NULL) kid->par = p;
    }
    void Splay(Node* x) {
        for(Node* p;x->par != NULL;Rotate(x)) {
            p = x->par;
            if(p->par != NULL) Rotate(Get_Child(x) == Get_Child(p) ? p : x); 
        }
    }
    void Insert(int key, void* val) {
        Node *temp = Root, *last = NULL;
        while(temp != NULL) {
            last = temp; 
            if(temp->key < key) { temp = temp->kid[1]; }
            else if(temp->key > key) { temp = temp->kid[0]; }
            else temp = NULL;
        }
        temp = (Node*)calloc(1, sizeof(Node));
        temp->key = key; temp->val = val; temp->par = last; 
        if(last != NULL) last->kid[last->key < key ? 1 : 0] = temp;
        Splay(temp);
        Root = temp; 
    }
    void Find(int key, void** prev, void** exact, void** next) {
        Node *temp = Root, *last = NULL;
        while(temp != NULL) { 
            last = temp;
            if(temp->key < key) temp = temp->kid[1];
            else if(temp->key > key) temp = temp->kid[0];  
            else if(temp->key == key) temp = NULL;
        }

        Splay(last);
        *prev = *exact = *next = NULL;
        if(last->key == key) {
            *exact = last->val;
        } else {
            if(last->key < key) {
                *prev = last->val;
                if(last->kid[1] != NULL) *next = last->kid[1]->val;
            } else {
                if(last->kid[0] != NULL) *prev = last->kid[0]->val;
                *next = last->val;
            }
        } 
    }
    void Free(Node* root) {
        if(root == NULL) return;
        for(int i = 0;i < 2;i++) Free(root->kid[i]);
        free(root);
    }
    void Print(Node* root) { printf("(%d, %d) - (%d %d %d) - %d\n", root->key, *(int*)root->val, root->kid[0], root->kid[1], root->par, root); }
    void Show(Node* root) {
        if(root == NULL) return;
        Show(root->kid[0]);
        Print(root);
        Show(root->kid[1]);
    }
};

int storage[100];
int main() {
    int N, i, temp;
    for(i = 0;i < 100;i++) storage[i] = i;
    while(scanf("%d", &N) != EOF) {
        SplayTree S = { .Root = NULL };
        for(i = 0;i < N;i++) {
            scanf("%d", &temp);
            S.Insert(temp, &storage[i]);
            S.Show(S.Root);
        }
        for(i = 0;i < N;i++) {
            scanf("%d", &temp);
            void *ans[3];
            S.Find(temp, &ans[0], &ans[1], &ans[2]);
            for(int j = 0;j < 3;j++) if(ans[j] != NULL) printf("%d\n", *(int*)ans[j]);
        }
        S.Free(S.Root);
    }
}
