#include <iostream>
#include <memory.h>
#define MAXN 500005
using namespace std;
long long int zkw[MAXN * 5][2] ,N ,Q ,leaf;
void init() {
    for(;leaf < N + 2;leaf <<= 1) ;
    for(int i = 1;i <= N;i++) {
        cin >> zkw[leaf + i][0];
        zkw[leaf + i][1] = zkw[leaf + i][0];
    }
    for(int i = leaf - 1;i;i--) {
        zkw[i][0] = min(zkw[i * 2][0] ,zkw[i * 2 + 1][0]);
        zkw[i][1] = max(zkw[i * 2][1] ,zkw[i * 2 + 1][1]);
    }
}

long long int query(int l ,int r) {
    long long int mini = (1LL << 63) - 1 ,maxi = -1;
    for(l += leaf - 1 ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
        if(l % 2 == 0) mini = min(mini ,zkw[l + 1][0]) ,maxi = max(maxi ,zkw[l + 1][1]);
        if(r % 2 == 1) mini = min(mini ,zkw[r - 1][0]) ,maxi = max(maxi ,zkw[r - 1][1]);
    }
    return maxi - mini;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,l ,r;
    while(cin >> N >> Q) {
        memset(zkw ,-1 ,sizeof(zkw));
        leaf = 1;
        init();
        while(Q--) {
            cin >> l >> r;
            if(l > r) throw;
            if(l <= 0 || N <= l || r <= 0 || N <= r) throw;
            cout << query(l ,r) << endl;
        }
    }
}
/*
10 5
10 9 8 7 6 5 4 3 2 1
1 3
*/
