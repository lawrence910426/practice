#include <iostream>

using namespace std;
const int MAXD = 39;
long long int pows[MAXD];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    long long int q ,N;
    int p;
    int i ,j;
    pows[0] = 1;
    for(i = 1;i < MAXD;i++) pows[i] = pows[i - 1] * 3;
    int factor[MAXD];
    for(cin >> q;q--;) {
        cin >> N;
        for(i = 0;i < MAXD;i++) factor[i] = 0;
        for(p = 0;N;N /= 3 ,p++) factor[p] = N % 3;
        for(i = 0;i < p;i++) {
            while(factor[i] >= 3) factor[i] -= 3 ,factor[i + 1] += 1;
            if(factor[i] == 2) {
                factor[i + 1] += 1;
                for(j = 0;j <= i;j++) factor[j] = 0;
            }
        }
        N = 0;
        for(i = 0;i < MAXD;i++) N += pows[i] * factor[i];
        cout << N << '\n';
    }
}
