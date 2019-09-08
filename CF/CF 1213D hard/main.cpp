#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

int freq[200005] ,cost[200005] ,data[200005];
int main() {
    int N ,K ,eax ,power ,ans;
    int i;
    while(cin >> N >> K) {
        memset(freq ,0 ,sizeof(freq));
        memset(cost ,0 ,sizeof(cost));
        for(i = 0;i < N;i++) cin >> data[i];
        sort(data ,data + N);
        ans = (1LL << 31) - 1;
        for(i = 0;i < N;i++) {
            power = 0;
            while(data[i]) {
                freq[data[i]] += 1;
                cost[data[i]] += power;
                if(freq[data[i]] >= K) ans = min(ans ,cost[data[i]]);
                power += 1;
                data[i] >>= 1;
            }
        }
        cout << ans << endl;
    }
}
