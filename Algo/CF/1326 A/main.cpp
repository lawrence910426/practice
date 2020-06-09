#include <iostream>

using namespace std;

int main() {
    int T ,N ,sum ,i;
    for(cin >> T;T--;) {
        cin >> N;
        if(N == 1) cout << -1;
        else {
            sum = 3 + (N - 1) * 2;
            if(sum % 3 == 0) {
                for(i = 0;i < N - 2;i++) cout << 2;
                cout << 33;
            } else {
                for(i = 0;i < N - 1;i++) cout << 2;
                cout << 3;
            }
        }
        cout << endl;
    }
}
