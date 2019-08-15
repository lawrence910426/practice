#include <iostream>
#include <memory.h>
#include <bitset>
#include <vector>
using namespace std;

#define N 100005
vector<int> ps;
bitset<10005> er;
int prime[N];

void sieve() {
    memset(prime ,0 ,sizeof(prime));
    for(int i = 2;i < N;i++) {
        if(prime[i] == 0) {
            ps.push_back(i);
            prime[i] = i;
        }
        for(int item : ps) {
            if(item * i >= N) break;
            prime[item * i] = item;
            if(i % item == 0) break;
        }
    }
}

int main() {
    sieve();
    long long int l ,r ,start ,ans;
    while(cin >> l >> r) {
        if(l > r) {
            cout << 0 << endl;
            continue;
        }
        er.reset();
        ans = (l == 1 ? 1 : 0);
        for(long long int p : ps) {
            if(l % p == 0) start = l;
            else start = l + p - l % p;
            if(start == p) start = p + p;

            for(;start <= r;start += p) {
                if(!er[start - l]) {
                    ans += 1;
                    er[start - l] = true;
                }
            }
        }
        cout << r - l + 1 - ans << endl;
    }
}
