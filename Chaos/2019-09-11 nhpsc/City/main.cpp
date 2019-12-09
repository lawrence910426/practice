#include <iostream>
#include <memory.h>

using namespace std;
const int MAXN = 1e5 + 50;
int leaf;
struct zkw {
    int data[MAXN * 3];
    void modify(int pos ,int val) { for(pos += leaf + 1;pos != 0;pos >>= 1) data[pos] += val; }
    int query(int l ,int r) {
        int ans = 0;
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(l % 2 == 0) ans += data[l ^ 1];
            if(r % 2 == 1) ans += data[r ^ 1];
        }
        return ans;
    }
} seg[20];

int raw[MAXN];
int main() {
    long long N ,Q ,c ,last_ans ,cmd ,L ,R ,l ,r ,x ,y;
    int i;
    while(cin >> N >> Q >> c) {
        last_ans = 0;
        for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
        for(i = 0;i < 20;i++) memset(seg[i].data ,0 ,sizeof(seg[i].data));
        for(i = 0;i < N;i++) {
            cin >> raw[i];
            seg[raw[i]].modify(i ,1);
        }
        while(Q--) {
            cin >> cmd;
            if(cmd == 1) {
                cin >> x >> y;
                x = (x + c * last_ans) % N;
                y = (y + c * last_ans) % 100000;
                seg[raw[x]].modify(x ,-1);
                seg[y].modify(x ,1);
                raw[x] = y;
            } else {
                cin >> L >> R >> l >> r;
                L = (L + c * last_ans) % N;
                R = (R + c * last_ans) % N;
                l = (l + c * last_ans) % N;
                r = (r + c * last_ans) % N;
                R += 1 ,r += 1;
                for(last_ans = i = 0;i < 20;i++) {
                    last_ans += seg[i].query(L ,R) * seg[i].query(l ,r);
                }
                cout << last_ans << endl;
            }
        }
    }
}
