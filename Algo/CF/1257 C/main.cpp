#include <iostream>
#include <map>
using namespace std;
const int MAXN = 2e5 + 10;
int data[MAXN];
int main() {
    int lptr ,rptr ,N ,T ,ans;
    int i;
    for(cin >> T;T--;) {
        cin >> N;
        for(i = 0;i < N;i++) cin >> data[i];

        ans = (1LL << 31) - 1;
        map<int ,int> m1 ,m2;
        for(lptr = rptr = 0;rptr < N;rptr++) {
            if(m1[data[rptr]] == 0) {
                m1[data[rptr]] = 1;
                m2[m1[data[rptr]]] = m2[m1[data[rptr]]] + 1;
            } else {
                m2[m1[data[rptr]]] = m2[m1[data[rptr]]] - 1;
                if(m2[m1[data[rptr]]] == 0) m2.erase(m1[data[rptr]]);
                m1[data[rptr]] = m1[data[rptr]] + 1;
                m2[m1[data[rptr]]] = m2[m1[data[rptr]]] + 1;
            }
            while(m2.rbegin()->second == 1 && rptr - lptr >= 1) {
                ans = min(ans ,rptr - lptr + 1);
                m2[m1[data[lptr]]] = m2[m1[data[lptr]]] - 1;
                if(m2[m1[data[lptr]]] == 0) m2.erase(m1[data[lptr]]);
                m1[data[lptr]] = m1[data[lptr]] - 1;
                if(m1[data[lptr]] == 0) m1.erase(data[lptr]);
                m2[m1[data[lptr]]] = m2[m1[data[lptr]]] + 1;
                lptr += 1;
            }
        }
        if(ans == (1LL << 31) - 1) cout << -1 << endl;
        else cout << ans << endl;
    }
}
