#include <iostream>
#include <assert.h>
const int MAXN = 512;
using namespace std;
struct st {
    st* kids[4];
    long long int sum;
    st() {}
    st(int s): sum(s) {}
} tree[MAXN * MAXN * 3];
struct seg {
    int L ,R ,U ,D;
    seg(seg self ,int style) {
        L = R = U = D = -1;
        if(self.L == self.R - 1 && self.U == self.D - 1) return;
        if(self.L == self.R - 1 && self.U != self.D - 1) {
            if(style == 0) L = self.L ,R = self.R ,U = self.U , D = (self.U + self.D) >> 1;
            if(style == 3) L = self.L ,R = self.R ,U = (self.U + self.D) >> 1 , D = self.D;
        } else if(self.L != self.R - 1 && self.U == self.D - 1) {
            if(style == 0) L = (self.L + self.R) >> 1 ,R = self.R ,U = self.U , D = self.D;
            if(style == 1) L = self.L ,R = (self.L + self.R) >> 1 ,U = self.U , D = self.D;
        } else {
            if(style == 0) L = (self.L + self.R) >> 1 ,R = self.R ,U = self.U , D = (self.U + self.D) >> 1;
            if(style == 1) L = self.L ,R = (self.L + self.R) >> 1 ,U = self.U , D = (self.U + self.D) >> 1;
            if(style == 2) L = self.L ,R = (self.L + self.R) >> 1 ,U = (self.U + self.D) >> 1 , D = self.D;
            if(style == 3) L = (self.L + self.R) >> 1 ,R = self.R ,U = (self.U + self.D) >> 1 , D = self.D;
        }
    }
    seg(int l, int r ,int u ,int d): L(l) ,R(r) ,U(u) ,D(d) {}
};

int used = 0;
st* build(seg s) {
    int on = used++;
    assert(on < MAXN * MAXN * 3);
    tree[on] = st(0);
    for(int i = 0;i < 4;i++) {
        seg ss = seg(s ,i);
        if(ss.L == -1) tree[on].kids[i] = nullptr;
        else tree[on].kids[i] = build(ss);
    }
    return &tree[on];
}

long long int query(st *t ,int L ,int R ,int U ,int D ,seg s) {
    if(t == nullptr) return 0;
    if(s.R <= L || R <= s.L || s.D <= U || D <= s.U)
        return 0;
    if(L <= s.L && s.R <= R && U <= s.U && s.D <= D)
        return t->sum;
    long long int ans = 0;
    for(int i = 0;i < 4;i++) ans += query(t->kids[i] ,L ,R ,U ,D ,seg(s ,i));
    return ans;
}

void modify(st *t ,int x ,int y ,int v ,seg s) {
    if(t == nullptr) return;
    if(s.L <= x && x < s.R && s.U <= y && y < s.D) {
        t->sum += v;
        for(int i = 0;i < 4;i++)
            modify(t->kids[i] ,x ,y ,v ,seg(s ,i));
    }
}

int main() {
    int N ,cmd ,a ,b ,c ,d;
    st *root = build(seg(0 ,MAXN ,0 ,MAXN));
    cin >> N;
    while(cin >> cmd) {
        if(cmd == 1) {
            cin >> a >> b >> c;
            modify(root ,a ,b ,c ,seg(0 ,MAXN ,0 ,MAXN));
        } else {
            cin >> a >> b >> c >> d;
            cout << query(root ,a ,c + 1 ,b ,d + 1 ,seg(0 ,MAXN ,0 ,MAXN)) << endl;
        }
    }
}
