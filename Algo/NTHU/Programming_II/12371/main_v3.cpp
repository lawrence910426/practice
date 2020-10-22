#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
const int MAXN = 1e3 + 50, C = 1;

class RollingHash {
    long long P, X;
public:
    RollingHash(long long p, long long x) { this->P = p; this->X = x; }
    void Occurences(string& hay, string& needle, bitset<MAXN>& occur) {
        long long needle_hash = 0, hay_hash = 0, temp = 1;
        int i;

        for(i = 0;i < (int)needle.size();i++) {
            temp = (temp * X) % P;
            needle_hash = (needle_hash + temp * needle[(int)needle.size() - 1 - i]) % P;
            hay_hash = (hay_hash + temp * hay[(int)needle.size() - 1 - i]) % P;
        }
         
        occur.reset();
        for(;i < (int)hay.size();i++) {
            occur[i - (int)needle.size()] = (needle_hash == hay_hash);
            hay_hash -= hay[i - (int)needle.size()] * temp;
            hay_hash = (hay_hash % P + P) % P;
            hay_hash = hay_hash * X + hay[i] * X;
            hay_hash = (hay_hash % P + P) % P;
        }
        occur[i - (int)needle.size()] = (needle_hash == hay_hash);
    }
} Hash[C] = {RollingHash(4272919189171LL, 880301LL)};
bitset<MAXN> occur[C];
vector<int> prefix = vector<int>(MAXN, 0);

string hay, needle;
int main() {
    int l, r, i, Q, ans;
    while(cin >> hay >> needle >> Q) {
        for(i = 0;i < C;i++) Hash[i].Occurences(hay, needle, occur[i]);
        for(i = C - 1;i >= 1;i--) occur[0] = occur[0] & occur[i];
        for(prefix[0] = i = 0;i < (int)hay.size();i++) prefix[i + 1] = prefix[i] + (occur[0][i] ? 1 : 0);
        ans = 0;
        while(Q--) {
            cin >> l >> r;
            if(r - (int)needle.size() + 1 >= 1) ans = max(ans, prefix[r - (int)needle.size() + 1] - prefix[l - 1]);
        }
        cout << ans << endl;
    }
}
