#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;


int main() {
    cout << fixed << setprecision(8);
    int T, N;
    int i, X, Y;
    for(cin >> T;T--;) {
        cin >> N;
        vector<long long> x, y;
        for(i = 0;i < N * 2;i++) {
            cin >> X >> Y;
            if(X == 0) y.push_back(abs(Y));
            if(Y == 0) x.push_back(abs(X));
        }
        sort(x.begin(), x.end()); sort(y.begin(), y.end());
        double ans = 0;
        for(i = 0;i < N;i++) ans += sqrt(x[i] * x[i] + y[i] * y[i]);
        cout << ans << endl;
    }
}
