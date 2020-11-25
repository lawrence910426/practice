#include <iostream>
#include <memory.h>
#include <bitset>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 50, INF = (1LL << 31) - 1;
int last[MAXN], raw[MAXN];
bitset<MAXN> mex;

class zkw {
    int storage[MAXN * 3], leaf;
public:
    zkw() { 
        for(leaf = 1;leaf < MAXN + 2;leaf <<= 1) ;
        for(int i = leaf * 2;i >= 0;i--) storage[i] = -1;
    }
    void Modify(int pos, int val) {
        pos += leaf + 1;
        storage[pos] = val;
        for(pos >>= 1;pos > 0;pos >>= 1) storage[pos] = min(storage[pos * 2], storage[pos * 2 + 1]);
    }
    int Query(int l, int r) {
        int mini = INF;
        for(l += leaf, r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
            if(l % 2 == 0) mini = min(mini, storage[l ^ 1]);
            if(r % 2 == 1) mini = min(mini, storage[r ^ 1]);
        }
        return mini;
    }
} seg;

int main() {
    memset(last, -1, sizeof(last));
    int N, ans;
    int i, temp;
    cin >> N;
    for(i = 0;i < N;i++) {
        cin >> raw[i];
        if(raw[i] > 1) {
            mex[1] = true;
            temp = seg.Query(1, raw[i]);
            if(last[raw[i]] < temp && temp < i) mex[raw[i]] = true;
        }
        seg.Modify(raw[i], i);
        last[raw[i]] = i;
    }
    for(i = 2;i <= N + 1;i++) if(last[i] < seg.Query(1, i)) mex[i] = true;
    for(ans = 1;mex[ans];ans++) ;
    cout << ans << endl;
}
