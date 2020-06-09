#pragma GCC optimize("Ofast")
#include <iostream>

using namespace std;
const int MAXN = 1e5;
long long diff[MAXN] ,data[MAXN] ,modify[MAXN] ,maxi[MAXN];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    long long N ,K ,mini ,profit;
    int i ,j;
    while(cin >> N >> K) {
        for(i = 0;i < N - 1;i++) cin >> diff[i];
        for(i = 0;i < K;i++) cin >> modify[i];
        for(data[0] = i = 0;i < N - 1;i++) data[i + 1] = data[i] + diff[i];
        if(K == 0) {
            mini = data[0] ,profit = 0;
            for(i = 1;i < N;i++) {
                profit = max(profit ,data[i] - mini);
                mini = min(data[i] ,mini);
            }
        } else if(K == 1) {
            maxi[N - 1] = data[N - 1];
            for(i = N - 2;i >= 0;i--) maxi[i] = max(maxi[i + 1] ,data[i]);
            mini = data[0] ,profit = 0;
            for(i = 1;i < N;i++) {
                profit = max(profit ,maxi[i] - mini);
                profit = max(profit ,maxi[i] - mini + modify[0] - diff[i - 1]);
                mini = min(data[i] ,mini);
            }
        } else {
            if(diff[0] >= 0) {
                profit = (N - 1) * diff[0];
                for(i = 0;i < K;i++) if(diff[0] < modify[i]) profit += modify[i] - diff[0];
            } else {
                profit = 0;
                for(i = 0;i < K;i++) if(0 < modify[i]) profit += modify[i];
            }
        }
        cout << profit << endl;
    }
}
