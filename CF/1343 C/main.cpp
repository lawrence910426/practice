#include <iostream>

using namespace std;

int main() {
    long long T, N, i, ans, pos, neg, temp;
    for(cin >> T;T--;) {
        pos = neg = ans = 0; cin >> N;
        for(i = 0;i < N;i++) {
            cin >> temp;
            if(temp > 0) {
                if(pos == 0) {
                    ans += neg;
                    pos = neg = 0;
                }
                pos = max(pos, temp);
            } else {
                if(neg == 0) {
                    ans += pos;
                    pos = neg = 0;
                }
                if(neg == 0) neg = temp;
                else neg = max(neg, temp);
            }
        }
        if(neg == 0) ans += pos;
        if(pos == 0) ans += neg;
        cout << ans << endl;
    }
}
