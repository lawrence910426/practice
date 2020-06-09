#include <iostream>
#include <memory.h>

using namespace std;
const int MAXN = 1e6 + 50;
int N ,data[MAXN] ,leaf ,bridge[MAXN];
struct zkw {
    int data[MAXN * 5];
    void update(int pos ,int diff) { for(pos += leaf + 1;pos;pos >>= 1) data[pos] += diff; }
    int query(int l ,int r) {
        int ans = 0;
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) ans += (l % 2 == 0 ? data[l ^ 1] : 0) + (r % 2 == 1 ? data[r ^ 1] : 0);
        return ans;
    }
    int get_pos(int nrank) {
        for(int ans = 1;true;) {
            if(ans > leaf) return ans - leaf - 1;
            if(data[ans * 2] >= nrank) ans = ans * 2;
            else nrank -= data[ans * 2] ,ans = ans * 2 + 1;
        }
    }
} seg[2];
int main() {
    int i ,lsum ,rsum ,lrank ,rrank ,conn ,ans;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> data[i];
        memset(seg[0].data ,0 ,sizeof(data)) ,memset(seg[1].data ,0 ,sizeof(data));
        for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
        for(i = 1;i < N;i++) seg[1].update(data[i] ,1);
        for(i = 0;i < N;i++) {
            if(i != 0) {
                seg[0].update(data[i - 1] ,1);
                seg[1].update(data[i] ,-1);
            }
            lsum = seg[0].query(data[i] + 1 ,N);
            rsum = seg[1].query(data[i] + 1 ,N);
            lrank = seg[0].query(0 ,data[i] + 1) + (lsum + 1) / 2;
            rrank = seg[1].query(0 ,data[i] + 1) + (rsum + 1) / 2;
            if(lsum == 0 && rsum == 0) continue;
            if(lsum != 0 && rsum == 0) conn = seg[0].get_pos(lrank);
            if(lsum == 0 && rsum != 0) conn = seg[1].get_pos(rrank);
            if(lsum != 0 && rsum != 0) conn = min(seg[0].get_pos(lrank) ,seg[1].get_pos(rrank));
            bridge[i] += 1 ,bridge[conn] += 1;
        }
        for(ans = i = 0;i < N;i++) ans = max(ans ,bridge[i]);
        cout << ans << '\n';
    }
}
