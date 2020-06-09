#include <iostream>
#include <set>
using namespace std;
const int MAXN = 100000 + 10;
long long int raw[MAXN];

int main() {
    int N ,K ,T;
    int i;
    long long int sum ,D ,val;
    multiset<long long int> s;
    for(cin >> T;T--;) {
        cin >> N >> K >> D;
        for(i = 0;i < N;i++) cin >> raw[i];
        s.clear();
        for(i = sum = 0;i < N - 1;i++) {
            sum += raw[i];
            if(raw[i] > 0 && raw[i + 1] < 0) {
                s.insert(sum);
                sum = 0;
            } else if(raw[i] < 0 && raw[i + 1] > 0) {
                s.insert(sum);
                sum = 0;
            }
        }
        sum += raw[i];
        s.insert(sum);
        for(sum = i = 0;i < N;i++) sum += raw[i];
        while(K--) {
            if(s.empty()) break;
            if(D >= 1) {
                val = *s.rbegin();
                if(val < 0) break;
                sum = sum + D * val - val;
                s.erase(prev(s.end()));
            } else {
                val = *s.begin();
                if(val > 0) break;
                sum = sum + D * val - val;
                s.erase(s.begin());
            }
        }
        cout << sum << endl;
    }
}
