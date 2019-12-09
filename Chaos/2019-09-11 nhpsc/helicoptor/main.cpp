#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int MAXN = 2e5 ,BUCKS = 300;
int N ,Q ,W ,ans ,weight;
int buckets[BUCKS] ,_clone[BUCKS];
int i ,j ,val ,x ,y ,tmp;
int raw[MAXN];
int main() {
    while(cin >> N >> Q >> W) {
        if(Q == 0) {
            multiset<int> S;
            for(i = 0;i < N;i++) {
                cin >> val;
                S.insert(val);
            }
            while(Q--) cin >> i;
            ans = 0;
            while(!S.empty()) {
                weight = W - *S.rbegin();
                S.erase(prev(S.end()));
                ans += 1;
                auto ptr = S.lower_bound(weight);
                if(ptr != S.end() && *ptr == weight) {
                    S.erase(ptr);
                } else if(ptr != S.begin()) {
                    ptr--;
                    S.erase(ptr);
                }
            }
            cout << ans << endl;
        } else {
            for(i = 0;i < BUCKS;i++) buckets[i] = 0;
            for(i = 0;i < N;i++) {
                cin >> raw[i];
                buckets[raw[i]] += 1;
            }

            do {
                ans = 0;
                for(i = 0;i < BUCKS;i++) _clone[i] = buckets[i];
                for(i = W;i > 0;i--) {
                    for(j = W - i;_clone[i] > 0 && j > 0;j--) {
                        if(i != j) {
                            if(_clone[j] <= 0) continue;
                            tmp = min(_clone[j] ,_clone[i]);
                            ans += tmp;
                            _clone[j] -= tmp;
                            _clone[i] -= tmp;
                        } else {
                            ans += _clone[i] / 2;
                            _clone[i] = _clone[i] % 2;
                        }
                    }
                    if(_clone[i] > 0) {
                        ans += _clone[i];
                        _clone[i] = 0;
                    }
                }
                cout << ans << endl;

                if(Q != 0) {
                    cin >> x >> y;
                    x -= 1;
                    //cout << x << " " << y << " " << raw[x] << " " << buckets[raw[x]] << " " << buckets[y] << endl;
                    buckets[raw[x]] -= 1;
                    buckets[y] += 1;
                    raw[x] = y;
                }
            } while(Q--);
        }
    }
}
