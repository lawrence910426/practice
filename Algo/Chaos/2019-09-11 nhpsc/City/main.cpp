#include <iostream>
#include <memory.h>
#include <map>

using namespace std;
const int MAXN = 1e5 + 50 ,MAXV = 15;
int leaf;
struct zkw {
    int data[MAXN * 5];
    void modify(int pos ,long long val) {
        for(pos += leaf + 1;pos != 0;pos >>= 1) data[pos] += val;
    }
    long long query(int l ,int r) {
        int ans = 0;
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(l % 2 == 0) ans += data[l ^ 1];
            if(r % 2 == 1) ans += data[r ^ 1];
        }
        return ans;
    }
} seg[MAXV];

int raw[MAXN];
int main() {
    long long N ,Q ,c ,last_ans ,cmd ,L ,R ,l ,r ,x ,y;
    int i;
    while(cin >> N >> Q >> c) {
        if(N <= 5000 && Q <= 5000 && c == 0) {
            for(i = 0;i < N;i++) cin >> raw[i];
            while(Q--) {
                cin >> cmd;
                if(cmd == 1) {
                    cin >> x >> y;
                    raw[x] = y;
                } else {
                    cin >> l >> r >> L >> R;
                    map<int ,long long> m1 ,m2;
                    for(i = l;i <= r;i++) m1[raw[i]] = m1[raw[i]] + 1;
                    for(i = L;i <= R;i++) m2[raw[i]] = m2[raw[i]] + 1;
                    auto p1 = m1.begin() ,p2 = m2.begin();
                    last_ans = 0;
                    while(!(p1 == m1.end() && p2 == m2.end())) {
                        if(p1 == m1.end()) p2++;
                        else if(p2 == m2.end()) p1++;
                        else if(p1->first < p2->first) p1++;
                        else if(p1->first > p2->first) p2++;
                        else {
                            last_ans += p1->second * p2->second;
                            p1++ ,p2++;
                        }
                    }
                    cout << last_ans << endl;
                }
            }
        } else {
            last_ans = 0;
            for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
            for(i = 0;i < MAXV;i++) memset(seg[i].data ,0 ,sizeof(seg[i].data));
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
                    for(last_ans = i = 0;i < MAXV;i++) last_ans += seg[i].query(L ,R) * seg[i].query(l ,r);
                    cout << last_ans << endl;
                }
            }
        }
    }
}
