#include <iostream>
#include <assert.h>
#include <algorithm>
#define max3(a ,b ,c) max(a ,max(b ,c))
using namespace std;
const int MAXIMUM = (1 << 24) + 1e6 ,MAXN = 1e5 + 50;
struct status { int lmax ,rmax ,maxi ,len; };
status join(status a ,status b) {
    int lmax = (a.lmax == a.len ? a.lmax + b.lmax : a.lmax);
    int rmax = (b.rmax == b.len ? a.rmax + b.rmax : b.rmax);
    int maxi = max3(a.maxi ,b.maxi ,a.rmax + b.lmax);
    return status{lmax ,rmax ,maxi ,a.len + b.len};
}
struct segment {
    int lptr ,rptr;
    status stat;
} tree[MAXIMUM];
int used;
int N ,Q ,C ,cmd ,pos ,l ,r ,color;
/* true -> addition ,false -> remove */
void modify(int id ,int pos ,int l ,int r ,bool type) {
    int mid = (l + r) / 2;
    if(l == r - 1) {
        if(type) tree[id].stat = status{0 ,0 ,0 ,1};
        else tree[id].stat = status{1 ,1 ,1 ,1};
    } else {
        if(l <= pos && pos < mid) {
            if(tree[id].lptr == -1) {
                tree[used].stat = status{mid - l ,mid - l, mid - l, mid - l};
                tree[id].lptr = used++;
            }
            modify(tree[id].lptr ,pos ,l ,mid ,type);
        } else {
            if(tree[id].rptr == -1) {
                tree[used].stat = status{r - mid ,r - mid ,r - mid, r - mid};
                tree[id].rptr = used++;
            }
            modify(tree[id].rptr ,pos ,mid ,r ,type);
        }
        status left = (tree[id].lptr == -1 || true ? status{mid - l ,mid - l, mid - l ,mid - l} : tree[tree[id].lptr].stat);
        status right = (tree[id].rptr == -1 || true ? status{r - mid ,r - mid ,r - mid ,r - mid} : tree[tree[id].rptr].stat);
        tree[id].stat = join(left ,right);
        assert(tree[id].stat.len == r - l);
    }
}
status query(int id ,int ql ,int qr ,int l ,int r) {
    if(qr <= l || r <= ql) return status{0 ,0 ,0 ,r - l};
    else {
        if(id == -1) {
            if(ql <= l && r <= qr) return status{r - l ,r - l ,r - l ,r - l};
            else return join(query(-1 ,ql ,qr ,l ,(l + r) / 2) ,query(-1 ,ql ,qr ,(l + r) / 2 ,r));
        } else {
            assert(tree[id].stat.len == r - l);
            if(ql <= l && r <= qr) return tree[id].stat;
            else return join(query(tree[id].lptr ,ql ,qr ,l ,(l + r) / 2) ,query(tree[id].rptr ,ql ,qr ,(l + r) / 2 ,r));
        }
    }
}
int raw[MAXN];
int main() {
    //ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i;
    cin >> N >> Q >> C;
    for(i = 0;i < MAXIMUM;i++) tree[i].lptr = tree[i].rptr = -1;
    for(used = 0;used < (1 << 24);used++) tree[used].stat = status{N ,N ,N ,N};
    for(i = 0;i < N;i++) {
        cin >> raw[i];
        modify(raw[i] ,i ,0 ,N ,true);
    }
    while(Q--) {
        cin >> cmd;
        if(cmd == 0) {
            cin >> pos >> color;
            modify(raw[pos] ,pos ,0 ,N ,false);
            modify(color ,pos ,0 ,N ,true);
            raw[pos] = color;
        } else {
            cin >> l >> r >> color;
            status ans = query(color ,l ,r ,0 ,N);
            if(ans.len > N) return -1;
            if(ans.len < N) throw;
            cout << ans.maxi << '\n';
        }
    }
}
