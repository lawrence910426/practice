#pragma GCC optimize("Ofast,no-stack-protector")
#include "lib1338.h"
#include <algorithm>

using namespace std;
const int MAXN = 1e6 + 5;
long long gcd_table[MAXN][20] ,mini_table[MAXN][20];

inline void init(int N, long long C[]) {
    int i ,j ,pos;
    for(j = 0;j < 20;j++) for(i = 0;i < N;i++) {
        if(j == 0) gcd_table[i][j] = mini_table[i][j] = C[i];
        else {
            pos = min(N - 1 ,i + (1 << (j - 1)));
            gcd_table[i][j] = __gcd(gcd_table[i][j - 1] ,gcd_table[pos][j - 1]);
            mini_table[i][j] = min(mini_table[i][j - 1] ,mini_table[pos][j - 1]);
        }
    }
}

inline int query(int L, int R) {
    int len = __lg(R - L);
    int gcd_ans = __gcd(gcd_table[L][len] ,gcd_table[R - (1 << len)][len]);
    int min_ans = min(mini_table[L][len] ,mini_table[R - (1 << len)][len]);
    return (gcd_ans == min_ans ? 1 : 0);
}
