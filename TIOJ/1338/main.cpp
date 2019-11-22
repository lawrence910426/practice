#include "lib1338.h"
#include <memory.h>
#include <set>
#include <vector>
#include <algorithm>
#include <bitset>
#include <iostream>

using namespace std;
const int MAXN = 1e5 + 5;

long long gcd(long long a ,long long b) { return (a % b == 0 ? b : gcd(b ,a % b)); }
long long zkw[MAXN * 3];
int leaf;
vector<long long> discrete;
bitset<MAXN> prefix[MAXN];

int discriminated(long long n) {
    auto it = lower_bound(discrete.begin() ,discrete.end() ,n);
    if(it == discrete.end() || *it != n) return -1;
    else return it - discrete.begin();
}

void init(int N, long long C[]) {
    int i;
    discrete = vector<long long>();
    for(i = 0;i < N;i++) discrete.push_back(C[i]);
    sort(discrete.begin() ,discrete.end());
    unique(discrete.begin() ,discrete.end());
    prefix[0].reset();
    for(i = 1;i <= N;i++) {
        prefix[i] = prefix[i - 1];
        prefix[i].flip(discriminated(C[i - 1]));
    }

    memset(zkw ,-1 ,sizeof(zkw));
    for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
    for(i = leaf + 1;i < leaf + 1 + N;i++) zkw[i] = C[i - leaf - 1];
    for(i = leaf - 1;i >= 1;i--) {
        if(zkw[i * 2] == -1 && zkw[i * 2 + 1] == -1) zkw[i] = -1;
        else if(zkw[i * 2] == -1 && zkw[i * 2 + 1] != -1) zkw[i] = zkw[i * 2 + 1];
        else if(zkw[i * 2] != -1 && zkw[i * 2 + 1] == -1) zkw[i] = zkw[i * 2];
        else zkw[i] = gcd(zkw[i * 2] ,zkw[i * 2 + 1]);
    }
}

int query(int L, int R) {
    int rawL = L ,rawR = R ,tmp;
    long long ans = zkw[L + leaf + 1];
    for(L = rawL + leaf ,R = rawR + leaf + 1;L ^ R ^ 1;L >>= 1, R >>= 1) {
        if(L % 2 == 0) ans = gcd(ans ,zkw[L ^ 1]);
        if(R % 2 == 1) ans = gcd(ans ,zkw[R ^ 1]);
    }
    bitset<MAXN> nums = prefix[rawR] ^ prefix[rawL];
    tmp = discriminated(ans);
    /*for(int i = 0;i < 10;i++) cout << nums[i] << " "; cout << endl;
    cout << ans << " " << tmp << endl;*/
    if(tmp == -1) return 0;
    else return (nums[tmp] ? 1 : 0);
}
