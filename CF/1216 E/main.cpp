#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
#define MAXN (~(1LL << 63))
vector<long long int> series ,sigma;

inline long long int power(int base ,int pow) {
    long long int ans = 1 ,tmp = pow;
    for(;pow;pow >>= 1) {
        if(pow & 1) ans *= tmp;
        tmp *= tmp;
    }
    return ans;
}

inline void build() {
    long long int value = 9 ,counter = 2 ,tmp ,previos;
    while(true) {
        series.push_back(value);
        tmp = counter * 9 * power(10 ,counter - 1);
        if(value >= MAXN - tmp) break;
        value += tmp;
    }
    previos = 1;
    for(long long int s : series) {
        tmp =
        previos = s;
    }
}

int main() {
    int q;
    long long int k;
    for(cin >> q;q--;) {

    }
}
//fuck you i'm out
