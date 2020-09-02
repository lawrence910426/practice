#pragma GCC optimize("Ofast")

#include <iostream>
#include <time.h>
#include <random>

using namespace std;
const int MAXN = 1e5 + 50;
int numbers[MAXN];

const int cert[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

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
    int first = clock();
    int N;
    int i, temp, a = 4, b = 9;
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for(i = 0;i < N;i++) {
        cin >> temp;
        numbers[i] = temp;
        if(!is_prime(temp)) {
            cout << "Yes" << '\n';
            return 0;
        } else if(N == 1) {
            cout << "No" << '\n';
            return 0;
        }
    }
    for(i = 0;!(i % 100 == 0 && clock() - first >= 1000);i++) {
        a = rand() % N;
        b = rand() % N;
        if(a == b) b = (b + 1) % N;
        temp = numbers[a] + numbers[b];
        if(!is_prime(temp)) {
            cout << "Yes" << '\n';
            return 0;
        }
    }
    cout << "No" << '\n';
    return 0;
}
/*
3
3 1 1
*/
