#include <iostream>
#include <vector>
#include <assert.h>
#define max(a ,b ,c) (max(a ,max(b ,c)))
using namespace std;
const int MAXC = 24 ,MAXN = 2e5 + 50;
struct seg {
    int lptr ,rptr ,lmax ,rmax ,maxi ,l ,r;
    seg(int lp ,int rp ,int lm ,int rm ,int ma ,int L ,int R): lptr(lp) ,rptr(rp) ,lmax(lm) ,rmax(rm) ,maxi(ma) ,l(L) ,r(R) {}
    seg(const seg& s): lptr(s.lptr) ,rptr(s.rptr) ,lmax(s.lmax) ,rmax(s.rmax) ,maxi(s.maxi) ,l(s.l) ,r(s.r) {}
    static seg join(seg a ,seg b) {
        assert(a.r == b.l);
        int ansl ,ansr ,ans;
        ansl = (a.lmax == a.r - a.l ? a.lmax + b.lmax : a.lmax);
        ansr = (b.rmax == b.r - b.l ? b.rmax + a.rmax : b.rmax);
        ans = max(a.maxi ,b.maxi ,a.rmax + b.lmax);
        return seg{-1 ,-1 ,ansl ,ansr ,ans ,a.l ,b.r};
    }
};
class st {
public:
    vector<seg> data;
    st() {}
    st(int N) {
        data = vector<seg>();
        data.push_back(seg(-1 ,-1 ,N ,N ,N ,0 ,N));
    }
    seg query(int id ,int l ,int r ,int L ,int R) {
        seg watch = data[id];
        if(id == -1) return seg(-1 ,-1 ,R - L ,R - L ,R - L ,L ,R);
        else if(r <= data[id].l || data[id].r <= l) return seg(-1 ,-1 ,0 ,0 ,0 ,L ,R);
        else if(data[id].l <= l && r <= data[id].r) return data[id];
        else return seg::join(query(data[id].lptr ,l ,r ,L ,(L + R) / 2), query(data[id].rptr ,l ,r ,(L + R) / 2 ,R));
    }
    /* type:true -> addition */
    /* type:false -> remove */
    void modify(int id ,int pos ,bool type) {
        int l = data[id].l ,r = data[id].r;
        if(l != r - 1) {
            int mid = (l + r) / 2 ,len = (r - l) / 2;
            if(l <= pos && pos < mid) {
                if(data[id].lptr == -1) {
                    data.push_back(seg(-1 ,-1 ,mid - l ,mid - l ,mid - l ,l ,mid));
                    data[id].lptr = data.size() - 1;
                }
                modify(data[id].lptr ,pos ,type);
            } else {
                if(data[id].rptr == -1) {
                    data.push_back(seg(-1 ,-1 ,r - mid ,r - mid ,r - mid ,mid ,r));
                    data[id].rptr = data.size() - 1;
                }
                modify(data[id].rptr ,pos ,type);
            }
            seg a = (data[id].lptr == -1 ? seg(-1 ,-1 ,len ,len ,len ,l ,mid) : data[data[id].lptr]);
            seg b = (data[id].rptr == -1 ? seg(-1 ,-1 ,len ,len ,len ,mid ,r) : data[data[id].rptr]);
            seg tmp = seg::join(a, b);
            data[id].maxi = tmp.maxi ,data[id].lmax = tmp.lmax ,data[id].rmax = tmp.rmax;
        } else {
            if(type) data[id].maxi = data[id].lmax = data[id].rmax = 0;
            else data[id].maxi = data[id].lmax = data[id].rmax = 1;
        }
    }
} *tree[1 << MAXC];
int N ,Q ,C;
int raw[MAXN];
int main() {
    int i ,color ,cmd ,pos ,l ,r;
    while(cin >> N >> Q >> C) {
        for(i = 0;i < (1 << C);i++) tree[i] = new st(N);
        for(i = 0;i < N;i++) {
            cin >> color;
            tree[color]->modify(0 ,i ,true);
            raw[i] = color;
        }
        while(Q--) {
            cin >> cmd;
            if(cmd == 0) {
                cin >> pos >> color;
                tree[color]->modify(0 ,pos ,true);
                tree[raw[pos]]->modify(0 ,pos ,false);
                raw[pos] = color;
            } else {
                cin >> l >> r >> color;
                cout << tree[color]->query(0 ,l ,r ,0 ,N).maxi << endl;
            }
        }
        for(i = 0;i < (1 << C);i++) delete tree[i];
    }
}
