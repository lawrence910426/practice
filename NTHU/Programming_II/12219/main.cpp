#include <iostream>

using namespace std;

int main() {
    unsigned long long x, y, m, temp, ans;
    cin >> x >> y >> m;
    
    temp = x % m; ans = 1;

    while(y > 0) {
        if(y & 1) ans = (ans * temp) % m;
        y >>= 1;
        temp = (temp * temp) % m;
    }

    cout << ans << endl;
}
