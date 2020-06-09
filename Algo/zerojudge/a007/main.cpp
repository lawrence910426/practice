#include <iostream>

using namespace std;
const int cert[6] = {2 ,7 ,11 ,13 ,61 ,199};

long long pow(long long base ,long long pow ,long long mod) {
    long long ans = 1 ,tmp = base;
    while(pow) {
        if(pow & 1) ans = (ans * tmp) % mod;
        tmp = (tmp * tmp) % mod;
        pow >>= 1;
    }
    return ans;
}

bool is_prime(int N) {
    for(int C : cert) if(C == N) return true;
    int tmp ,result;
    for(int C : cert) {
        bool non_prime = true;
        for(tmp = N - 1;tmp % 2 == 0;tmp >>= 1) {
            result = pow(C ,tmp ,N);
            if(result == 1 || result == N - 1) non_prime = false;
        }
        result = pow(C ,tmp ,N);
        if(result == 1 || result == N - 1) non_prime = false;
        if(non_prime) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N;
    while(cin >> N) cout << (is_prime(N) ? "質數" : "非質數") << '\n';
}
