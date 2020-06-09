#include <iostream>

using namespace std;

int data[200005];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,M ,K ,ans ,modulo;
    int i ,l ,r;
    while(cin >> N >> M >> K) {
        for(i = 0;i < N;i++) cin >> data[i];
        if(N / (K * 2 + 1) == 0) ans = data[0];
        else {
            modulo = N % (K * 2 + 1);
            if(modulo == 0) {
                l = -1;
                r = N;
                ans = 0;
            } else if(modulo <= K) {
                ans = data[0] + data[N - modulo];
                l = K;
                r = N - modulo - K;
            } else {
                ans = data[modulo - K] + data[N - K];
                l = modulo;
                r = N - K - K;
            }
            for(l += K + 1;l < r;l += K * 2 + 1) ans += data[l];
        }
        cout << ans << endl;
    }
}
/*
6 2 1
3 3 3 1 3 2

3 8 1
6 9 6

5 2 1
3 5 4 5 3

7 1 2
2 2 3 2 3 2 2

7 7 1
7 7 1 1 2 2 2
*/
