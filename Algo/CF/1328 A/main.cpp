#include <iostream>

using namespace std;

int T ,A ,B ,l ,r ,ans;
int main() {
    for(cin >> T;T--;) {
        cin >> A >> B;
        if(A % B == 0) ans = 0;
        else ans = (A + B - 1) / B * B - A;
        cout << ans << endl;
    }
}
