#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const unsigned long long MAXN = 0xFEDCBA9876543210;

unsigned long long P(unsigned long long A, unsigned long long B) {
    if(A < B) return 0;
    unsigned long long ans = 1;
    for(unsigned long long i = A - B + 1;i <= A;i++) ans = ans * i;
    return ans;
}

unsigned long long F(unsigned long long N, unsigned long long system) {
    if(N == 0) return 0;
    vector<unsigned long long> digit;
    for(unsigned long long temp = N;temp > 0;temp /= system) digit.push_back(temp % system);
    reverse(digit.begin(), digit.end());
    vector<bool> used = vector<bool>(digit.size(), false);

    unsigned long long ans = 1;
    for(unsigned long long i = 1;i < digit.size();i++) ans += P(system, digit.size() - i) - P(system - 1, digit.size() - 1 - i);
    for(unsigned long long i = 0;i < digit.size();i++) {
        for(int j = 0;j < digit[i];j++) {
            if((i == 0 && j == 0) || used[j]) continue;
            if(system - i - 1 >= 0) ans += P(system - i - 1, digit.size() - i - 1);
        }
        if(used[digit[i]]) break;
        used[digit[i]] = true;
    }
    return ans;
}

int main() {
    int N, query_type;
    char value_type;
    cin >> N;
    while(N--) {
        cin >> value_type >> query_type;
        unsigned long long system = (value_type == 'd' ? 10 : 16), l = 0, r = MAXN + 1, mid, p;
        cout << (value_type == 'd' ? dec : hex);
        cin >> (value_type == 'd' ? dec : hex);
        if(query_type == 0) {
            cin >> l >> r;
            cout << F(min(r, MAXN) + 1, system) - F(l, system) << endl;
        } else {
            cin >> p;
            while(l != r - 1) {
                mid = l + (r - l) / 2;
                if(F(mid, system) >= p) r = mid;
                else l = mid;
            }
            if(l == MAXN) cout << "-" << endl;
            else cout << l << endl;
        }
    }
}
