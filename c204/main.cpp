#include <iostream>
#include <vector>
#include <memory.h>

#define N 1000005LL
#define MAXI 1e13
using namespace std;

long long int prime[N];
vector<int> ps;

inline void linear_sieve() {
    memset(prime ,-1 ,sizeof(prime));
    ps = vector<int>();
    for(int i = 2;i < N;i++) {
        if(prime[i] == -1) {
            prime[i] = i;
            ps.push_back(i);
        }
        for(int j = 0;j < ps.size();j++) {
            if(ps[j] * i >= N) break;
            prime[ps[j] * i] = ps[j];
            if(i % ps[j] == 0) break;
        }
    }
}

inline long long int mini_factor(long long int a) {
    if(a < N) return prime[a];
    else for(int i = 0;i < ps.size();i++) if(a % ps[i] == 0) return ps[i];
    return a;
}

inline long long int series_sum(long long int base ,long long int count) {
    long long int sum = 0, mul = 1;
    while(true) {
        if(sum > MAXI - mul) return -1;
        sum += mul;
        if(--count == 0) break;
        if(mul > MAXI / base) return -1;
        mul *= base;
    }
    return sum;
}

int main()
{
    linear_sieve();
    long long int number ,mfact ,T ,pnum ,sum ,ans ,ssum ,number2;
    vector<pair<long long int ,long long int> > factor;
    int i;
    for(cin >> T;T--;) {
        factor = vector<pair<long long int ,long long int> >(); pnum = -1;
        cin >> number; number2 = number * 2;
        while(number != 1) {
            mfact = mini_factor(number);
            if(pnum == mfact) sum += 1;
            else {
                if(pnum != -1) factor.push_back(make_pair(pnum ,sum));
                pnum = mfact;
                sum = 1;
            }
            number /= mfact;
        }
        factor.push_back(make_pair(pnum ,sum));

        ans = 1;
        for(i = 0;i < factor.size();i++) {
            ssum = series_sum(factor[i].first ,factor[i].second + 1);
            if(ssum == -1) break;
            if(ans > MAXI / sum) break;
            ans *= ssum;
        }
        if(i == factor.size()) {
            if(number2 == ans) cout << "perfect" << endl;
            if(number2 > ans) cout << "deficient" << endl;
            if(number2 < ans) cout << "abundant" << endl;
        } else cout << "abundant" << endl;
    }
}
