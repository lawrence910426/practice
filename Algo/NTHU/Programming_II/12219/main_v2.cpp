#include <iostream>

using namespace std;

int main() {
    long long x, y, m;
    cin >> x >> y >> m;
    long long temp = x % m, ans = 1;
    while(y > 0) {
        if(y & 1) ans = (ans * temp) % m;
        temp = (temp * temp) % m;
        y >>= 1;
    }
    cout << ans % m << endl;
}

