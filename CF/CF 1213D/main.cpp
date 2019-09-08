#include <iostream>
#include <memory.h>
#include <queue>

#define MAXN 200005
using namespace std;
int N ,K ,sum[MAXN] ,ans;
const int intmax = (1LL << 31) - 1;

int getbest(int from) {
    int cost = 0 ,requrire = K;
    queue<pair<int ,int> > next;
    for(next.push(pair<int ,int>(from ,0));!next.empty();next.pop()) {
        if(cost >= ans) return intmax;
        pair<int ,int> F = next.front();
        if(F.first >= MAXN) continue;
        if(sum[F.first] >= requrire) {
            cost += requrire * F.second;
            requrire = 0;
            break;
        } else {
            requrire -= sum[F.first];
            cost += sum[F.first] * F.second;
            next.push(pair<int ,int>(F.first << 1 ,F.second + 1));
            next.push(pair<int ,int>((F.first << 1) + 1 ,F.second + 1));
        }
    }
    return (requrire == 0 ? cost : intmax);
}

int main() {
    int i ,eax ,maxi;
    while(cin >> N >> K) {
        memset(sum ,0 ,sizeof(sum));
        maxi = -1;
        for(i = 0;i < N;i++) {
            cin >> eax;
            maxi = max(maxi ,eax);
            sum[eax] += 1;
        }
        ans = intmax;
        for(i = 1;i <= maxi;i++) ans = min(ans ,getbest(i));
        cout << ans << endl;
    }
}
