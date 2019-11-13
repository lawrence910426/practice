#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <map>
#include <cmath>

using namespace std;
const int MAXN = 5e6 + 10;

inline int func(auto p ,int mid) {
    long long cnt;
    int val = 0;
    for(cnt = p.first;mid / cnt;cnt *= p.first) val += mid / cnt;
    return val;
}

inline int bsearch(auto p) {
    int l = 0 ,r = 1e7 ,mid ,val;
    while(l != r - 1) {
        mid = (l + r) >> 1;
        val = func(p ,mid);
        if(val >= p.second) r = mid;
        if(val < p.second) l = mid;
    }
    return (func(p ,l) == p.second ? l : l + 1);
}

int factor[MAXN] ,prime[MAXN] ,used;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);

    int i ,j;
    used = 0;
    for(i = 0;i < MAXN;i++) factor[i] = i;
    for(i = 2;i < MAXN;i++) {
        if(factor[i] == i) prime[used++] = i;
        for(j = 0;j < used;j++) {
            if(i * prime[j] >= MAXN) break;
            factor[i * prime[j]] = prime[j];
            if(i % prime[j] == 0) break;
        }
    }

    map<int ,int> N_factor;
    int Q ,N ,K;
    for(cin >> Q;Q--;) {
        cin >> N;
        for(N_factor = map<int ,int>();N != 1;N /= factor[N]) N_factor[factor[N]] = N_factor[factor[N]] + 1;
        K = 0;
        for(auto p : N_factor) K = max(bsearch(p) ,K);
        cout << K << '\n';
    }
}
