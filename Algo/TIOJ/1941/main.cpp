#include <iostream>
using namespace std;

const int MAXN = 8e5 + 10 ,root = 1;
inline int max(int a ,int b) { return (a > b ? a : b); }
int N;
struct seg {
    int L ,R ,val;
    bool slide ,pure;
    seg(): L(-1) ,R(-1) {}
}tree[MAXN * 5];

void pull_up(int id) {
    if(tree[id].L == tree[id].R - 1) return;
    if(tree[id * 2].pure && tree[id * 2].slide && tree[id * 2 + 1].pure && tree[id * 2 + 1].slide) {
        tree[id].pure = true;
        tree[id].slide = true;
    }
    if(tree[id * 2].pure && !tree[id * 2].slide && tree[id * 2 + 1].pure && !tree[id * 2 + 1].slide) {
        tree[id].pure = true;
        tree[id].slide = false;
    }
}

void build(int id ,int L ,int R) {
    tree[id].L = L ,tree[id].R = R;
    tree[id].val = 0;
    tree[id].slide = false ,tree[id].pure = true;
    if(L != R - 1) {
        build(id * 2 ,L ,(L + R) / 2);
        build(id * 2 + 1 ,(L + R) / 2 ,R);
    }
}

void modify_add(int id ,int L ,int R ,int lazy) {
    if(tree[id].L == -1 || tree[id].R == -1) return;
    if(R <= tree[id].L || tree[id].R <= L) return;
    if(L <= tree[id].L && tree[id].R <= R) {
        tree[id].val += lazy;
    } else {
        modify_add(id * 2 ,L ,R ,lazy);
        modify_add(id * 2 + 1 ,L ,R ,lazy);
    }
}

void modify_slide(int id ,int L ,int R) {
    if(tree[id].L == -1 || tree[id].R == -1) return;
    if(R <= tree[id].L || tree[id].R <= L) return;
    if(L <= tree[id].L && tree[id].R <= R && tree[id].pure) {
        if(!tree[id].slide) {
            tree[id].slide = true;
            modify_add(root ,R ,N ,tree[id].R - tree[id].L);
        }
    } else {
        modify_slide(id * 2 ,L ,R);
        modify_slide(id * 2 + 1 ,L ,R);
    }
    pull_up(id);
}

int finalize(int id ,int lazy) {
    if(tree[id].L == -1 || tree[id].R == -1) return -1;
    if(tree[id].L == tree[id].R - 1) return tree[id].val;
    if(tree[id].slide) return max(finalize(id * 2 ,tree[id].val + lazy) ,finalize(id * 2 + 1 ,tree[id].val + lazy + (tree[id].R - tree[id].L) / 2));
    else return max(finalize(id * 2 ,tree[id].val + lazy) ,finalize(id * 2 + 1 ,tree[id].val + lazy));
}

int main() {
    int M ,L ,R;
    while(cin >> N) {
        build(root ,0 ,N);
        for(M = N;M--;) {
            cin >> L >> R;
            modify_slide(root ,L ,R + 1);
            cout << "Maximum:" << finalize(root ,0) << endl;
        }
    }
}
