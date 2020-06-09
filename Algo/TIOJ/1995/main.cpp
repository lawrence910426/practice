#include "lib1995.h"
#include <cstdio>
#include <memory.h>
const int MAXN = 1e6+50;
const int MAXQ = 8e5+50;
using namespace std;
int N ,Q ,leaf ,zkw[MAXN * 4] ,qs[MAXQ][2];

#define max(a ,b) (a > b ? a : b)
inline void init() {
    //memset(zkw ,0 ,sizeof(zkw));
    int i;
    for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
    for(i = 1;i < N + 1;i++) scanf("%d" ,&zkw[i + leaf]);
    for(i = leaf - 1;i > 0;i--) zkw[i] = max(zkw[i * 2] ,zkw[i * 2 + 1]);
}

inline int query(int l ,int r) {
    int ans = -1;
    for(l = leaf + l - 1 ,r = leaf + r + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
        if(l % 2 == 0) ans = max(ans ,zkw[l ^ 1]);
        if(r % 2 == 1) ans = max(ans ,zkw[r ^ 1]);
    }
    return ans;
}

int main() {
    int i;
    while(scanf("%d %d\n" ,&N ,&Q) != EOF) {
        for(i = 0;i < Q;i++) scanf("%d %d\n" ,&qs[i][0] ,&qs[i][1]);
        init();
        for(i = 0;i < Q;i++) printf("%d\n" ,query(qs[i][0] ,qs[i][1]));
    }
}

/*
6 3
1 4
5 5
3 6
7 3 13 6 1 18
*/
