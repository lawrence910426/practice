#include <iostream>
#include <cstring>
const long long mod = 1e9 + 7;
const int MAXN = 1e5 + 50;

class Combinations {
    long long stair[MAXN];
    long long pow(long long base, long long pow) {
        long long ans = 1, temp = base;
        while(pow > 0) {
            if(pow & 1) ans = (ans * temp) % mod;
            temp = (temp * temp) % mod;
            pow >>= 1;
        }
        return ans;
    }

public:
    Combinations() {
        stair[0] = stair[1] = 1;
        for(long long i = 2;i < MAXN;i++) stair[i] = (stair[i - 1] * i) % mod;
    }
    long long Get(long long a, long long b) {
        long long ans = stair[a];
        ans = (ans * pow(stair[b], mod - 2)) % mod;
        ans = (ans * pow(stair[a - b], mod - 2)) % mod;
        return ans;
    }
} C;


int main() {
    std::string s;
    int pos, maxi, value, i;
    long long ans;
    while(std::cin >> s) {
        for(i = 1;i < s.size();i++) if(s[i - 1] > s[i]) break;
        ans = (i == s.size() ? 1 : 0);
        ans = (ans + C.Get(s.size() - 1 + 9, 9)) % mod;

        maxi = 1;
        for(pos = 0;pos < s.size();pos++) {
            value = s[pos] - '0';
            if(value < maxi) break;
            for(i = maxi;i < value;i++) ans = (ans + C.Get(8 - i + s.size() - pos, s.size() - pos - 1)) % mod;
            maxi = std::max(maxi, value);
        }
        std::cout << (ans - 1 + mod) % mod << '\n';
    }
}
