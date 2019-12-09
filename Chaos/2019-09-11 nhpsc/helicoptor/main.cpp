#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int MAXN = 2e5;
int N ,Q ,W ,ans ,weight;
int main() {
    int i ,val;
    while(cin >> N >> Q >> W) {
        multiset<int> S;
        for(i = 0;i < N;i++) {
            cin >> val;
            S.insert(val);
        }
        while(Q--) cin >> i;
        ans = 0;
        while(!S.empty()) {
            weight = W - *S.rbegin();
            //cout <<*S.rbegin() << " ";
            S.erase(prev(S.end()));
            ans += 1;
            auto ptr = S.lower_bound(weight);
            if(ptr != S.end() && *ptr == weight) {
                S.erase(ptr);
                //cout << *ptr << " ";
            } else if(ptr != S.begin()) {
                ptr--;
                S.erase(ptr);
                //cout << *ptr << " ";
            }
            //cout << endl;
        }
        cout << ans << endl;
    }
}
