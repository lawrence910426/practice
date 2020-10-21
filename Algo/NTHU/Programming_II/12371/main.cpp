#pragma GCC optimize("Ofast")

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 1e3 + 50, C = 3;
const long long mod[C] = {179424719, 1000000007, 179424731};

string raw, needle;
class Hash {
    long long p, x = 2, prefix[MAXN];
    long long power(long long base, long long pow) {
        long long temp = base, ans = 1;
        pow %= (p - 1);
        while(pow > 0) {
            if(pow & 1) ans = (ans * temp) % p;
            pow >>= 1;
            temp = (temp * temp) % p;
        }
        return ans;
    }

public:
    Hash() {}
    Hash(string& s, long long p) {
        prefix[0] = 0;
        long long temp = x;
        for(int i = 0;i < s.size();i++) {
            prefix[i + 1] = (prefix[i] + (s[i] * temp) % p) % p;
            temp = (temp * x) % p;
        }
        this->p = p;
    }
    
    long long Get_Hash(int l, int r) { return ((prefix[r] - prefix[l]) * power(x, (p - 2) * l)) % p; }
};

int prefix[MAXN];
int main() {
    int Q, ans, l, r;
    int i, j;
    bool flag;

    ios::sync_with_stdio(0); cin.tie(0);
    while(cin >> raw >> needle >> Q) {
        Hash raw_hash[C], needle_hash[C];
        for(j = 0;j < C;j++) { raw_hash[j] = Hash(raw, mod[j]); needle_hash[j] = Hash(needle, mod[j]); }
        for(prefix[0] = i = 0;i + needle.size() <= raw.size();i++) {
            flag = true;
            for(j = 0;j < C;j++) flag &= raw_hash[j].Get_Hash(i, i + needle.size()) == needle_hash[j].Get_Hash(0, needle.size());
            prefix[i + 1] = prefix[i] + (flag ? 1 : 0);        
        }

        ans = 0;
        while(Q--) {
            cin >> l >> r;
            ans = max(ans, prefix[r] - prefix[l - 1]);    
        }
        cout << ans << '\n';

        //cout << endl;
    }
}
