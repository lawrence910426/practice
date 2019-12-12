#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
const int MAXP = (1LL << 20) + 50 ,MAXQ = 200005;
int primes[MAXP];
vector<int> ps;
void linear_sieve() {
    int i;
    for(i = 0;i < MAXP;i++) primes[i] = i;
    for(i = 2;i < MAXP;i++) {
        if(primes[i] == i) ps.push_back(i);
        for(int p : ps) {
            if(p * i >= MAXP) break;
            primes[i * p] = p;
            if(i % p == 0) break;
        }
    }
}
bitset<MAXQ> ersieve;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    linear_sieve();
    int T ,L ,R ,i ,ans;
    for(cin >> T;T--;) {
        cin >> L >> R;
        ersieve.reset();
        for(int p : ps) {
            for(i = (L + p - 1) / p;i * p <= R;i++) ersieve[i * p - L] = true;
            if(L <= p && p <= R) ersieve[p - L] = false;
        }
        for(ans = i = 0;i <= R - L;i++) if(!ersieve[i]) ans += 1;
        cout << ans << '\n';
    }
}
