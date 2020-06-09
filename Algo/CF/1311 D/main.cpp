#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;
const int INF = (1LL << 31) - 1 ,MAXN = 1e4 + 50;
int T ,A ,B ,C ,ans ,a ,b, c;
int i ,j ,k;

int main() {
    for(cin >> T;T--;) {
        cin >> A >> B >> C;
        ans = INF;
        for(i = 1;i < MAXN;i++) for(j = i;j < MAXN;j += i) for(k = j;k < MAXN;k += j)
            if(abs(i - A) + abs(j - B) + abs(k - C) < ans) {
                ans = abs(i - A) + abs(j - B) + abs(k - C);
                a = i; b = j; c = k;
            }
        cout << ans << endl;
        cout << a << " " << b << " " << c << endl;
    }
}
