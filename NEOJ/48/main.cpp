#include <iostream>
#include <memory.h>
using namespace std;
struct BinaryTree { int l ,r ,val; } tree[10000];
int N = 0 ,raw[10000] ,i ,counter = 1;

void put(int val) {
    int on = 1;
    while(true) {
        if(val < tree[on].val) {
            if(tree[on].l == 0) {
                tree[on].l = counter;
                tree[counter].val = val;
                counter += 1;
                return;
            } else on = tree[on].l;
        }
        if(val > tree[on].val) {
            if(tree[on].r == 0) {
                tree[on].r = counter;
                tree[counter].val = val;
                counter += 1;
                return;
            } else on = tree[on].r;
        }
    }
}

void dfs(int on) {
    if(tree[on].l != 0) dfs(tree[on].l);
    if(tree[on].r != 0) dfs(tree[on].r);
    cout << tree[on].val << endl;
}

int main() {
    int i;
    memset(tree ,0 ,sizeof(tree));
    while(cin >> raw[N]) N += 1;
    tree[counter++].val = raw[0];
    for(i = 1;i < N;i++) put(raw[i]);
    dfs(1);
}
