#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <climits>

using namespace std;
struct pt {
    int D1 ,D2;
}data[1000005];
int maxi[1000005];
int x ,y ,x1 ,y1 ,x2 ,y2 ,N;
bool cmp(pt a ,pt b) { return a.D1 < b.D1; }

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i;
    long long int ans ,tmp;
    while(cin >> x1 >> y1 >> x2 >> y2 >> N) {
        for(i = 0;i < N;i++) {
            cin >> x >> y;
            data[i].D1 = (x - x1) * (x - x1) + (y - y1) * (y - y1);
            data[i].D2 = (x - x2) * (x - x2) + (y - y2) * (y - y2);
        }
        sort(data ,data + N ,cmp);

        maxi[N - 1] = data[N - 1].D2;
        for(i = N - 2;i >= 0;i--) maxi[i] = max(maxi[i + 1] ,data[i].D2);

        ans = maxi[0];
        for(i = 0;i < N;i++) {
            tmp = data[i].D1;
            if(i != N - 1) tmp += maxi[i + 1];
            if(tmp < ans) ans = tmp;
        }
        cout << ans << '\n';
    }
}
