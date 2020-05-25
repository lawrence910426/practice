#include <iostream>

using namespace std;

int main() {
    int T, a, b, i;
    for(cin >> T;T--;) {
        cin >> a;
        for(i = 0, b = 4;i < 29;i += 1, b <<= 1) {
            if(a % (b - 1) == 0) {
                cout << a / (b - 1) << endl;
                break;
            }
        }
    }
}
