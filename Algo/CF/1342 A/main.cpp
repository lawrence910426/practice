#include <iostream>

using namespace std;

int main() {
    long long T, x, y, a, b, ans;
    for(cin >> T;T--;) {
        ans = 0;
        cin >> x >> y >> a >> b;
        if(x > y) swap(x, y);
        if(x == 0 && y == 0) { cout << 0 << endl; continue; }
        /*if(x == 0) {
            if(x == y) {
                if(a < b) { x += 1; ans += a; }
                else { x += 1; y += 1; ans += b * 2; }
            } else { x += 1; ans += a; }
        }*/
        ans += a * (y - x);
        ans += min(b * x, a * x * 2);
        cout << ans << endl;
    }
}
