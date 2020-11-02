#include <stdio.h>
#include <cstdlib>

const int MAXN = 1e2 + 5;
struct Node {
    struct Node *l, *r; int val;
    static void Show(Node* ptr) {
        if(ptr == NULL) return;
        printf("%d ", ptr->val);
        Show(ptr->l);
        Show(ptr->r);
    }
} *Tree[MAXN];

struct SplayTree {
    struct Node { struct Node *kid[2], *par; int key; void *val; } *Root = NULL;
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
        if(!Root) return;
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
                if(last->kid[1]) *next = last->kid[1]->val;
            } else {
                if(last->kid[0]) *prev = last->kid[0]->val;
                *next = last->val;
            }
        } 
    }
    void Free(Node* root) {
        if(root == NULL) return;
        for(int i = 0;i < 2;i++) Free(root->kid[i]);
        free(root);
    }
    void Print(Node* root) { /* printf("(%d, %d) - (%d %d %d) - %d\n", root->key, *(int*)root->val, root->kid[0], root->kid[1], root->par, root); */ }
    void Show(Node* root) {
        if(root == NULL) return;
        Show(root->kid[0]);
        Print(root);
        Show(root->kid[1]);
    }
};

int N, inorder[MAXN], postorder[MAXN], dummy[MAXN], cases = 0;
int main() {
    int i, pos;
    for(i = 0;i < MAXN;i++) dummy[i] = i;
    void *l, *m, *r;
    Node *left, *right, *root;
    while(scanf("%d", &N) != EOF) {
        SplayTree Inv, Near;
        for(i = 0;i < N;i++) Tree[i] = (Node*)calloc(1, sizeof(Node));
        for(i = 0;i < N;i++) scanf("%d", &inorder[i]);
        for(i = 0;i < N;i++) Inv.Insert(inorder[i], &dummy[i]);
        for(i = 0;i < N;i++) scanf("%d", &postorder[i]);
        for(i = N - 1;i >= 0;i--) {
            printf("%d\n", pos);
            Inv.Find(postorder[i], &l, &m ,&r);
            pos = *(int*)m; 

            Tree[pos]->val = postorder[i];
            if(i == N - 1) {
                root = Tree[pos];
            } else {
                printf("qwerqwer\n");
                Near.Find(pos, &l, &m, &r);
                left = (Node*)l; right = (Node*)r;
                if(left && left->r == NULL) { left->r = Tree[pos]; }
                else { right->l = Tree[pos]; }
            }
            Near.Insert(pos, &Tree[pos]);
        }
        Inv.Free(Inv.Root); Near.Free(Near.Root); 
        printf("testcase%d: ", ++cases); Node::Show(root); printf("\n");
        for(i = 0;i < N;i++) free(Tree[i]);
    }
}
