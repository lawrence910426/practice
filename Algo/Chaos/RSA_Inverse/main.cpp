#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;
const int MAXN = 1e6;
vector<int> ps; int prime[MAXN];
long long N = 13886599, e, d = 707147, phi, msg = 7217220;

void sieve() {
    memset(prime, 0, sizeof(prime));
    for(int i = 2;i < MAXN;i++) {
        if(prime[i] == 0) { prime[i] = i; ps.push_back(i); }
        for(int p : ps) {
            if(i * p >= MAXN) break;
            prime[i * p] = p;
            if(i % p == 0) break;
        }
    }
}


/* 有取得加密後的文件代碼為7217220且已知公鑰為 (e,N) = (252323,13886599) */
int main() {
    sieve();
    for(int p : ps) if(N % p == 0) phi = (p - 1) * (N / p - 1);
    cout << phi << endl;

    long long temp = msg, ans = 1, pow = d;
    while(pow > 0) {
        if(pow % 2 == 1) ans = (ans * temp) % 13886599;
        temp = (temp * temp) % 13886599;
        pow >>= 1;
    }
    cout << ans << endl;
}
