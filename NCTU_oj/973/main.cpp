///#pragma GCC optimize("Ofast")
#include <iostream>
#include <assert.h>

using namespace std;
const int MAXN = 1e5 + 10;
int raw[MAXN];
struct seg {
    int L ,R;
    long long int value;
    inline seg(): L(-1) ,R(-1) ,value(0) {}
    inline seg(int l ,int r ,int v): L(l) ,R(r) ,value(v) {}
    inline bool operator< (seg s) { return value < s.value; }
    inline bool operator> (seg s) { return value > s.value; }
    inline bool operator== (seg s) { return value == s.value; }
    inline seg operator+ (seg s) {
        if(L == -1 && R == -1) return s;
        if(s.L == -1 && s.R == -1) return seg(L ,R ,value);
        return seg(L ,s.R ,value + s.value);
    }
    inline void show() { cout << "[" << L << "," << R << "," << value << "]"; }
    inline int len() { return R - L; }
};
struct stree {
    stree *l ,*r;
    int tag;
    bool used;
    seg lseg[2] ,rseg[2] ,tarseg[2] ,self; //0-min ,1-max
    inline stree(): l(nullptr) ,r(nullptr) ,tag(1) ,used(false) {}
    inline void show() {
        cout << "self "; self.show(); cout << "\ttag: " << tag << "\tused:" << used << endl;
        cout << "lseg "; lseg[0].show(); cout << "\t\t"; lseg[1].show(); cout << endl;
        cout << "rseg "; rseg[0].show(); cout << "\t\t"; rseg[1].show(); cout << endl;
        cout << "tarseg "; tarseg[0].show(); cout << '\t'; tarseg[1].show(); cout << endl;
    }
};
inline seg max(seg a ,seg b) { return (a == b ? (a.len() > b.len() ? b : a) : (a > b ? a : b)); }
inline seg max(seg a ,seg b ,seg c) { return max(a ,max(b ,c)); }
inline seg max(seg a ,seg b ,seg c ,seg d) { return max(max(a ,b) ,max(c ,d)); }
inline seg min(seg a ,seg b) { return (a == b ? (a.len() > b.len() ? b : a) : (a < b ? a : b)); }
inline seg min(seg a ,seg b ,seg c) { return min(a ,min(b ,c)); }
inline seg min(seg a ,seg b ,seg c ,seg d) { return min(min(a ,b) ,min(c ,d)); }

inline void merge(stree*& ans ,stree* left ,stree* right) {
    if(left == nullptr || right == nullptr) return;
    ans->self = left->self + right->self;
    if(left->used && !right->used) {
        ans->lseg[0] = ans->lseg[1] = seg();
        ans->rseg[0] = right->rseg[0];
        ans->rseg[1] = right->rseg[1];
        ans->tarseg[0] = right->tarseg[0];
        ans->tarseg[1] = right->tarseg[1];
    } else if(!left->used && right->used) {
        ans->lseg[0] = left->lseg[0];
        ans->lseg[1] = left->lseg[1];
        ans->rseg[0] = ans->rseg[1] = seg();
        ans->tarseg[0] = left->tarseg[0];
        ans->tarseg[1] = left->tarseg[1];
    } else if(left->used && right->used) {
        ans->lseg[0] = ans->lseg[1] = ans->rseg[0] = ans->rseg[1] = ans->tarseg[0] = ans->tarseg[1] = seg();
    } else {
        ans->lseg[0] = min(seg() ,left->lseg[0] ,left->self + right->lseg[0]);
        ans->lseg[1] = max(seg() ,left->lseg[1] ,left->self + right->lseg[1]);
        ans->rseg[0] = min(seg() ,right->rseg[0] ,left->rseg[0] + right->self);
        ans->rseg[1] = max(seg() ,right->rseg[1] ,left->rseg[1] + right->self);
        ans->tarseg[0] = min(seg() ,left->tarseg[0] ,right->tarseg[0] ,left->rseg[0] + right->lseg[0]);
        ans->tarseg[1] = max(seg() ,left->tarseg[1] ,right->tarseg[1] ,left->rseg[1] + right->lseg[1]);
    }
}

inline void push(stree* s) {
    if(s->used && s->tag == 1) return;
    s->self = seg(s->self.L ,s->self.R ,s->self.value * s->tag);
    if(s->l != nullptr && s->r != nullptr) {
        s->l->tag *= s->tag;
        s->r->tag *= s->tag;
        assert(s->l->used == false && s->r->used == false);
        s->l->used = s->used;
        s->r->used = s->used;
    }
    s->tag = 1;
}

stree* build(int L ,int R) {
    stree* ans = new stree();
    ans->self = seg(L ,R ,raw[L]);
    if(L == R - 1)  {
        ans->lseg[0] = ans->lseg[1] = ans->rseg[0] = ans->rseg[1] = ans->tarseg[0] = ans->tarseg[1] = seg(L ,R ,raw[L]);
    } else {
        ans->l = build(L ,(L + R) / 2);
        ans->r = build((L + R) / 2 ,R);
    }
    return ans;
}

void rebuild(stree* s) {
    if(s == nullptr) return;
    push(s);
    rebuild(s->l);
    rebuild(s->r);
    merge(s ,s->l ,s->r);
}

void update(stree* st ,int L ,int R ,int D) {
    if(st == nullptr) return;
    if(st->self.R <= L && R <= st->self.L) return;
    if(L <= st->self.L && st->self.R <= R) {
        assert(st->used == false);
        st->tag = D;
        st->used = true;
    } else {
        update(st->l ,L ,R ,D);
        update(st->r ,L ,R ,D);
    }
}

void release(stree* st) {
    if(st == nullptr) return;
    release(st->l) ,release(st->r);
    delete st;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int T ,N ,K ,D ,l ,r ,i;
    stree *root;
    seg min_seg ,max_seg;
    for(cin >> T;T--;) {
        cin >> N >> K >> D;
        for(i = 0;i < N;i++) cin >> raw[i];
        root = build(0 ,N);
        //root->show();
        while(K--) {
            rebuild(root);
            min_seg = root->tarseg[0] ,max_seg = root->tarseg[1];
            if(D <= 0) {
                if(min_seg.L == -1) break;
                update(root ,min_seg.L ,min_seg.R ,D);
            } else {
                if(max_seg.L == -1) break;
                update(root ,max_seg.L ,max_seg.R ,D);
            }
            //root->show();
        }
        rebuild(root);
        cout << root->self.value << endl;
        release(root);
    }
}
/*
10
5 2 -1
-1 -1 1 -1 -4
*/
