#pragma GCC optimize("Ofast")
#include <iostream>

using namespace std;
const int MAXN = 5e5 + 50;
struct node { int l ,r ,maxi ,val; } data[MAXN * 10];
class st {
    int root ,used;
    int Build(int l ,int r) {
        int self = used; used += 1;
        if(l == r - 1) data[self] = node{-1 ,-1 ,0 ,0};
        else data[self] = node{Build(l ,(l + r) / 2) ,Build((l + r) / 2 ,r) ,0 ,0};
        return self;
    }
    int Query(int id ,int l ,int r ,int ql ,int qr) {
        if(qr <= l || r <= ql) return -1;
        if(ql <= l && r <= qr) return data[id].maxi;
        else return max(Query(data[id].l ,l ,(l + r) / 2 ,ql ,qr) ,Query(data[id].r ,(l + r) / 2 ,r ,ql ,qr));
    }
    void Modify(int id ,int l ,int r ,int pos ,int val) {
        if(pos < l || r <= pos) return;
        if(l == r - 1) data[id].maxi = data[id].val = val;
        else {
            Modify(data[id].l ,l ,(l + r) / 2 ,pos ,val);
            Modify(data[id].r ,(l + r) / 2 ,r ,pos ,val);
            data[id].maxi = 0;
            if(data[id].l != -1) data[id].maxi = max(data[id].maxi ,data[data[id].l].maxi);
            if(data[id].r != -1) data[id].maxi = max(data[id].maxi ,data[data[id].r].maxi);
        }
    }
public:
    void Modify(int pos ,int val) { Modify(root ,0 ,MAXN ,pos ,val); }
    int Query(int l ,int r) { return Query(root ,0 ,MAXN ,l ,r); }
    st() { used = 0; root = Build(0 ,MAXN); }
} seg;

int N ,Q ,l ,r ,val; int i;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while(cin >> N) {
        seg = st();
        for(i = 0;i < N;i++) { cin >> val; seg.Modify(i ,val); }
        for(cin >> Q;Q--;) {
            cin >> l >> r;
            if(l > r) swap(l ,r);
            cout << seg.Query(l - 1 ,r) << '\n';
        }
    }
}
