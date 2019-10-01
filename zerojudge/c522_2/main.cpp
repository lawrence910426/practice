#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <memory.h>
#define MAXN 500005
using namespace std;

struct t { int left ,right ,dsu_index; } tree[MAXN * 37];
struct d { int boss ,depth; } dsu[MAXN * 5];
int tcount ,dcount ,N ,version ,roots[MAXN];

int build(int l ,int r) {
    int tid = tcount++;
    if(l + 1 == r) {
        tree[tid].dsu_index = dcount;
        dsu[dcount].boss = l ,dsu[dcount].depth = 1;
        dcount += 1;
    } else {
        tree[tid].left = build(l ,(l + r) >> 1);
        tree[tid].right = build((l + r) >> 1 ,r);
    }
    return tid;
}

int query(int root ,int l ,int r ,int index) {
    if(l + 1 == r) return tree[root].dsu_index;
    int mid = (l + r) >> 1;
    if(index < mid) return query(tree[root].left ,l ,mid ,index);
    if(mid <= index) return query(tree[root].right ,mid ,r ,index);
}

inline int modify(int root ,int index ,int boss ,int depth) {
    int l = 0 ,r = N + 1 ,mid ,new_root = -1;
    while(l + 1 != r) {
        mid = (l + r) >> 1;
        if(new_root == -1) new_root = tcount;
        if(index < mid) {
            tree[tcount].left = tcount + 1;
            tree[tcount].right = tree[root].right;
            root = tree[root].left;
            r = mid;
        } else {
            tree[tcount].left = tree[root].left;
            tree[tcount].right = tcount + 1;
            root = tree[root].right;
            l = mid;
        }
        tcount += 1;
    }
    tree[tcount].dsu_index = dcount;
    dsu[dcount].depth = depth ,dsu[dcount].boss = boss;
    dcount += 1 ,tcount += 1;
    return new_root;
}

int boss(int root ,int i) {
    int dsu_index = query(root ,0 ,N + 1 ,i);
    return (i == dsu[dsu_index].boss ? dsu_index : boss(root ,dsu[dsu_index].boss));
}

inline int join(int root ,int a ,int b) {
    a = boss(root ,a) ,b = boss(root ,b);
    if(dsu[a].depth < dsu[b].depth)
        return modify(root ,dsu[a].boss ,dsu[b].boss ,dsu[a].depth);
    if(dsu[a].depth > dsu[b].depth)
        return modify(root ,dsu[b].boss ,dsu[a].boss ,dsu[b].depth);
    if(dsu[a].depth == dsu[b].depth) {
        int new_root = modify(root ,dsu[a].boss ,dsu[b].boss ,dsu[b].depth);
        return modify(new_root ,dsu[b].boss ,dsu[b].boss ,dsu[b].depth + 1);
    }
}

inline bool same(int root ,int a ,int b) {
    a = dsu[boss(root ,a)].boss ,b = dsu[boss(root ,b)].boss;
    return a == b;
}

inline int get_ans(int a ,int b) {
    int l = 0, r = version + 1 ,mid;
    while(l + 1 != r) {
        mid = (l + r) >> 1;
        if(same(roots[mid] ,a ,b)) r = mid;
        else l = mid;
    }
    if(same(roots[l + 1] ,a ,b)) return l + 1;
    else return l;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int a ,b ,M;
    while(cin >> N >> M) {
        tcount = dcount = 0;
        memset(tree ,-1 , sizeof(tree));
        memset(dsu ,-1 ,sizeof(dsu));
        roots[version] = build(0 ,N + 1);
        for(version = 1;version <= M;version++) {
            cin >> a >> b;
            roots[version] = roots[version - 1];
            if(!same(roots[version] ,a ,b)) {
                roots[version] = join(roots[version] ,a ,b);
                cout << "Mukyu" << '\n';
            } else {
                cout << get_ans(a ,b) << '\n';
            }
        }
    }
}
/*
3 3
1 2
2 3
1 3

2 3
2 1
1 2
2 1

6 8
1 2
2 1
1 3
4 3
3 2
3 5
1 5
1 4
*/
