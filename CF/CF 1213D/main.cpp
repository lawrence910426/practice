#include <iostream>
#include <memory.h>
#include <queue>

#define MAXN 200005
using namespace std;
int N ,K ,sum[MAXN];

int getbest(int from) {
    int cost = 0 ,amount = 0;
    queue<pair<int ,int> > next;
    for(next.push(pair<int ,int>(from ,0));!next.empty();next.pop()) {
        pair<int ,int> F = next.front();
        if(F.first >= MAXN) continue;
        if(amount + sum[F.first] > K) {
            amount += (K - sum[F.first]);
            cost += (K - sum[F.first]) * F.second;
            break;
        } else {
            amount += sum[F.first];
            cost += sum[F.first] * F.second;
            next.push(pair<int ,int>(F.first << 1 ,F.second + 1));
            next.push(pair<int ,int>(F.first << 1 + 1 ,F.second + 1));
        }
    }
    return (amount == K ? cost : -1);
}

int main() {
    int ans;
    int i ,eax;
    while(cin >> N >> K) {
        memset(sum ,0 ,sizeof(sum));
        for(i = 0;i < N;i++) {
            cin >> eax;
            sum[eax] += 1;
        }
        for(ans = i = 0;i < MAXN;i++) ans = max(ans ,getbest(i));
        cout << ans << endl;
    }
}
