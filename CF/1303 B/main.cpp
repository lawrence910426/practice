#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int cheat = 0;
    long long T ,N ,G ,B ,xg ,mini ,L ,R ,fix ,ans;
    for(cin >> T;T--;) {
        cin >> N >> G >> B;
        if(G >= B) cout << N << endl;
        else {
            mini = (N + 1) / 2; xg = (mini + G - 1) / G;
            L = (xg - 1) * (G + B); R = L + G;
            if(N <= L) {
                fix = G * xg - mini;
                ans = xg * (G + B) - B - fix;
            } else if(L < N && N <= R) {
                fix = G * xg - mini;
                ans = xg * (G + B) - B - fix;
            } else if(R < N) {
                fix = xg * (G + B) - N;
                ans = xg * (G + B) - fix;
            } else return -1;
            cout << max(ans ,N) << endl;
        }
    }
}
/*
2
2 1 3
*/
