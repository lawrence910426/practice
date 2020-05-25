#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <memory.h>
#include <map>
#include <algorithm>

using namespace std;
const int MAXN = 1e6;
const long long mod = 1e9 + 7;

class Sieve {
    int prime[MAXN]; vector<int> ps;
public:
    Sieve() {
        int i;
        for(i = 1;i < MAXN;i++) prime[i] = i;
        for(i = 2;i < MAXN;i++) {
            if(prime[i] == i) { ps.push_back(i); }
            for(int j : ps) {
                if(i * j >= MAXN) break;
                prime[i * j] = j;
                if(i % j == 0) break;
            }
        }
    }

    map<int ,int> factorization(int value) {
        map<int ,int> ans;
        int factor;
        for(factor = value;value != 1;value /= factor) {
            if(value >= MAXN) {
                for(int p : ps) if(value % p == 0) { factor = p; break; }
            } else factor = prime[value];
            ans[factor] = ans[factor] + 1;
        }
        return ans;
    }
} linear_sieve;


class Matrix {
    const static int siz = 5;
public:
    long long data[siz][siz], temp[siz][siz];
    void Multiply(Matrix& mat) {
        int i, j, k;
        for(i = 0;i < siz;i++) for(j = 0;j < siz;j++) temp[i][j] = 0;
        for(i = 0;i < siz;i++) for(j = 0;j < siz;j++) for(k = 0;k < siz;k++) { temp[i][j] += data[i][k] * mat.data[k][j]; temp[i][j] %= mod }
        for(i = 0;i < siz;i++) for(j = 0;j < siz;j++) data[i][j] = temp[i][j];
    }
    Matrix(bool transfer = true) {
        memset(data, 0, sizeof(data));
        if(transfer) data[0][0] = data[0][1] = data[0][2] = data[0][3] = data[1][0] = data[2][1] = data[3][3] = data[3][4] = data[4][4] = 1;
    }
};

void join_primes(vector<int>& primes, map<int, int>& factors) { for(auto p : factors) primes.push_back(p.first); }
Matrix power(Matrix& base, int pow) {
    Matrix ans, temp;
    while(pow != 0) {
        if(pow & 1) ans.Multiply(temp);
        temp.Multiply(temp);
        pow >>= 1;
    }
}

int main() {
    long long c, f1, f2 ,f3 ,n;
    cin >> c;
    auto factor_c = linear_sieve.factorization(c), factor_f1 = linear_sieve.factorization(f1),
         factor_f2 = linear_sieve.factorization(f2), factor_f3 = linear_sieve.factorization(f3);
    vector<int> primes;
    join_primes(primes, factor_c); join_primes(primes, factor_f1); join_primes(primes, factor_f2); join_primes(primes, factor_f3);
    sort(primes.begin(), primes.end()); primes.erase(unique(primes.begin(), primes.end()), primes.end());
    for(int p : primes) {

    }

}
