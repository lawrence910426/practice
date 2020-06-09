#include <iostream>

using namespace std;
const int MAXN = 1e6 ,MAXV = 1e6;

int raw[MAXN] ,N ,Q;
struct seg {
    seg *l ,*r ,*parent;
    int sum;
    seg(seg *L ,seg *R ,seg *P ,int S): l(L) ,r(R) ,parent(P) ,sum(S) {}
    static void pull_up(seg*& ans) {
        ans->sum = ans->l->sum + ans->r->sum;
        ans->l->parent = ans->r->parent = ans;
    }
    static seg *init(int l ,int r) {
        if(l == r - 1) return new seg(nullptr ,nullptr ,nullptr ,0);
        else {
            int mid = (l + r) >> 1;
            seg *ans = new seg(init(l ,mid) ,init(mid ,r) ,nullptr ,0);
            pull_up(ans);
            return ans;
        }
    }
    static seg *modify(seg* s ,int l ,int r ,int pos ,int value) {
        if(l == r - 1) return new seg(nullptr ,nullptr ,nullptr ,s->sum + value);
        else {
            seg *ans = new seg(s->l ,s->r ,s->parent ,s->sum);
            int mid = (l + r) >> 1;
            if(pos < mid) ans->l = modify(s->l ,l ,mid ,pos ,value);
            else ans->r = modify(s->r ,mid ,r ,pos ,value);
            pull_up(ans);
            return ans;
        }
    }
    static int query(seg* s ,int l ,int r ,int qL ,int qR) {
        if(qL <= l && r <= qR) return s->sum;
        if(qR <= l || r <= qL) return 0;
        int mid = (l + r) / 2;
        return query(s->l ,l ,mid ,qL ,qR) + query(s->r ,mid ,r ,qL ,qR);
    }
} *roots[MAXN];
void build() {
    roots[0] = seg::init(0 ,MAXV);
    for(int i = 1;i < N + 1;i++) roots[i] = seg::modify(roots[i - 1] ,0 ,MAXV ,raw[i - 1] ,1);
}
int get_value(int l ,int r ,int nrank) {
    int ansL = 0 ,ansR = MAXV ,ansM ,queryL ,queryR;
    while(ansL != ansR - 1) {
        ansM = (ansL + ansR) >> 1;
        queryL = seg::query(roots[l] ,0 ,MAXV ,0 ,ansM);
        queryR = seg::query(roots[r] ,0 ,MAXV ,0 ,ansM);
        if(queryR - queryL > nrank) ansR = ansM;
        if(queryR - queryL <= nrank) ansL = ansM;
    }
    return ansL;
}
int main() {
    int i ,l ,r ,nrank;
    while(cin >> N >> Q) {
        for(i = 0;i < N;i++) cin >> raw[i];
        build();
        while(Q--) {
            cin >> l >> r >> nrank;
            cout << get_value(l - 1 ,r ,nrank - 1) << endl;
        }
    }
}
/*
5 5
25957 6405 15770 26287 26465
2 2 1
3 4 1
4 5 1
1 2 2
4 4 1

*/
