#include <iostream>
#include <assert.h>

using namespace std;
const int MAXN = 1e5 + 10;
int raw[MAXN];
struct seg {
    int L ,R ,value;
    seg() {}
    seg(int l ,int r ,int v): L(l) ,R(r) ,value(v) {}
    bool operator< (seg s) { return value < s.value; }
    bool operator< (seg s) { return value > s.value; }
    seg operator+ (seg s) {
        assert(R + 1 == s.L);
        return seg(L ,s.R ,value + s.value);
    }
};
struct stree {
    stree *l ,*r;
    int tag;
    seg lseg[2] ,rseg[2] ,tarseg[2] ,self; //0-min ,1-max
    stree(): l(nullptr) ,r(nullptr) ,tag(0) {}
};
void pull(stree& ans ,stree left ,stree right) {
    ans->self = left->self + right->self;

    ans->lseg[0] = min(left->lseg[0] ,left->sum + right->lseg[0]);
    ans->lseg[1] = max(left->lseg[1] ,left->sum + right->lseg[1]);

    ans->rseg[0] = min(right->rseg[0] ,left->rseg[0] + right->self);
    ans->rseg[1] = max(right->rseg[1] ,left->rseg[1] + right->self);

    ans->lseg[0] = min(left->lseg[0] ,left->sum + right->lseg[0]);
    ans->lseg[1] = max(left->lseg[1] ,left->sum + right->lseg[1]);
}

stree* build(int L ,int R) {
    stree* ans = new stree(L ,R);
    if(L == R - 1)  {
        ans->sum = raw[L];
        ans->self = ans->lseg[0] = ans->lseg[1] = ans->rseg[0] = ans->rseg[1] = ans->tarseg[0] = ans->tarseg[1] = seg(L ,R ,raw[L]);
    } else {
        int mid = (L + R) / 2;
        stree *left = build(L ,mid) ,*right = build(mid ,R);
        ans->l = left ,ans->r = right;

    }
    return ans;
}
seg query(stree* ,int L ,int R) {

}
void update(stree* ,int L ,int R ,int D) {

}

int main() {

}
