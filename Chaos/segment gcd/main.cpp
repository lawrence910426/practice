#include <iostream>
#include <algorithm>
#include <assert.h>
#pragma GCC optimize("Ofast,no-stack-protector")
#define MAXN 1000005
using namespace std;

int N;
long long int zkw[MAXN * 10];
int leaf;
long long int ans ,L ,rl ,rr ,rmid ,R;

inline void build() {
    int i;
    for(leaf = 1;leaf <= N;leaf <<= 1) ;
    for(i = 0;i < MAXN * 10;i++) zkw[i] = 1;
    for(i = 0;i < N;i++) cin >> zkw[i + leaf + 1];
    for(i = leaf - 1;i > 0;i--) zkw[i] = __gcd(zkw[i << 1] ,zkw[(i << 1) ^ 1]);
}

inline long long int query(int l ,int r) {
    long long int ans = zkw[leaf + l + 1];
    for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
        if(l % 2 == 0) ans = __gcd(ans ,zkw[l ^ 1]);
        if(r % 2 == 1) ans = __gcd(ans ,zkw[r ^ 1]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N) {
        ans = 0;
        build();
        for(L = 0;L < N;L++) {
            rl = L + 1 ,rr = N;
            while(rl + 1 < rr) {
                rmid = (rl + rr) >> 1;
                if(query(L ,rmid) == 1) rr = rmid;
                else rl = rmid;
            }
            R = -1;
            if(query(L ,rl) == 1 && query(L ,rl + 1) == 1) R = rl - 1;
            if(query(L ,rl) != 1 && query(L ,rl + 1) == 1) R = rl;
            if(query(L ,rl) != 1 && query(L ,rl + 1) != 1) R = rl + 1;
            assert(R != -1);
            ans += N - R;
        }
        cout << ans << endl;
    }
}
/*


*/
