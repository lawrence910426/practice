#include <stdio.h>
#include <unordered_map>

const long long MOD = 1e9 + 7;

long long qpow(long long exp) {
    long long ans = 1, temp = 2;
    while(exp != 0) {
        if(exp & 1) ans = (ans * temp) % MOD;
        temp = (temp * temp) % MOD;
        exp >>= 1;
    }
    return ans;
}

int main() {
    int N, Q;
    int i, val;
    while(scanf("%d %d", &N, &Q) != EOF) {
        std::unordered_map<long long, int> occur;
        for(i = 1;i <= N;i++) {
            scanf("%d(/`A`)/ ~I__I ", &val);
            val = (val != 0 && val % 2 == 0 ? qpow(val / 2) : 0);
            if(occur.find(val) == occur.end()) occur[val] = i;
        }
        while(Q--) {
            scanf("%d", &val);
            if(occur.find(val) == occur.end()) printf("Go Down Chicken 404\n");
            else printf("%d\n", occur.find(val)->second);
        }
    }
}
