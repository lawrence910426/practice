#include <stdlib.h>

typedef struct _NODE {
	int level;
	struct _NODE *left_child, *right_child;
} Node;

int query_heatstroke(Node *now, int x) {
    while(now != NULL) {
        if(now->level == x) return 1;
        if(now->level < x) now = now->right_child;
        else now = now->left_child;
    }
    return 0;
}

void eat_rat(Node **root, int x) {
    if((*root)->level == x) {
        Node *top, *l = (*root)->left_child, *r = (*root)->right_child;
        if(l == NULL && r == NULL) top = NULL;
        if(l == NULL && r != NULL) top = r;
        if(l != NULL && r == NULL) top = l;
        if(l != NULL && r != NULL) {
            top = l;
            Node* pos = l;
            while(pos->right_child != NULL) pos = pos->right_child;
            pos->right_child = r; 
        }
        free(*root);
        *root = top;
    } else {
        if((*root)->level < x) {
            eat_rat(&(*root)->right_child, x);
        } else {
            eat_rat(&(*root)->left_child, x); 
        }
    }
}

void buy_rat(Node **root, int x) {
    if(*root == NULL) {
        *root = (Node*)calloc(1, sizeof(Node));
        (*root)->level = x;
    } else {
        Node *pos = *root, *last = NULL;
        while(pos != NULL) {
            last = pos;
            if(pos->level < x) pos = pos->right_child;
            else pos = pos->left_child;
        }
        Node *append = (Node*)calloc(1, sizeof(Node));
        append->level = x;
        if(last->level < x) last->right_child = append;
        else last->left_child = append; 
    }
}

void build_tree(Node **now, int *arr, int l, int r) {
    for(int i = l;i <= r;i++) buy_rat(now, arr[i]);
}

