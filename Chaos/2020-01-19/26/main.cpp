#pragma GCC optimize("unroll-loops")
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int x ,a = 10 ,i ,j;
    bool good;
    for(a = 2;true;a++) {
        for(x = 1;x < 1e9;x++) {
            for(i = x;i < x + a - 1;i++) {
                good = false;
                for(j = i + 1;j < x + a;j++) good |= (__gcd(i ,j) != 1);
                if(!good) break;
            }
            if(i == x + a - 1) cout << x << " " << a << endl;
        }
        cout << a << endl;
    }
    cout << "None" << endl;
}
