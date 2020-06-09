#include <iostream>

using namespace std;
int main() {
    int T, N, i; bool flag;
    for(cin >> T;T--;) {
        cin >> N;
        if((N / 2) % 2 == 0) {
            cout << "YES" << endl; flag = true;
            for(i = 2;i <= N * 2;i += 4) { cout << i + (flag ? 0 : -2) << " "; flag = !flag; }
            for(i = 1;i <= N * 2;i += 4) cout << i << " ";
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
