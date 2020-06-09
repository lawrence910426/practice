#include <iostream>
#include <map>
#include <set>
#include <bitset>

using namespace std;
const int MAXN = 5e3 + 10;
int data[MAXN];
int main() {
    int T, N ,ans ,frags ,left ,right;
    int i ,j;
    for(cin >> T;T--;) {
        cin >> N;
        for(i = 1;i <= N;i++) cin >> data[i];
        ans = 0;
        for(i = 1;i <= N;i++) {
            bitset<MAXN> bs;
            frags = 0;
            bs.reset();
            for(j = i;j <= N;j++) {
                if(bs[data[j]]) continue;
                if(bs[data[j] - 1] && bs[data[j] + 1]) frags -= 1;
                if(bs[data[j] - 1] && !bs[data[j] + 1]) frags += 0;
                if(!bs[data[j] - 1] && bs[data[j] + 1]) frags += 0;
                if(!bs[data[j] - 1] && !bs[data[j] + 1]) frags += 1;
                bs[data[j]] = true;
                if(frags == 1 && i != j) {
                    /* cout << i << " " << j << " " << data[i] << " " << data[j] << endl; */
                    left = min(data[i] ,data[j]) ,right = max(data[i] ,data[j]);
                    if(abs(data[j] - data[i]) == abs(j - i) && !bs[left - 1] && bs[left] && bs[right] && !bs[right + 1]) ans += 1;
                }
            }
        }
        cout << ans << endl;
    }
}
