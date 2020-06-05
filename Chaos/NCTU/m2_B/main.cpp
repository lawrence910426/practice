#include <iostream>

using namespace std;

int main() {
    int T, N, l, r, mid;
    long long K, temp, A, B, C;
    for(cin >> T;T--;) {
        cin >> N >> K; K -= 1;

        l = 0; r = N;
        while(l != r - 1) {
            temp = mid = (l + r) / 2;
            temp = (temp) * (temp + 1) * (temp + 2) / 6;
            if(temp > K) r = mid;
            else l = mid;
        }
        A = l; K -= A * (A + 1) * (A + 2) / 6;

        l = 0; r = N;
        while(l != r - 1) {
            temp = mid = (l + r) / 2;
            temp = (temp) * (temp + 1) / 2;
            if(temp > K) r = mid;
            else l = mid;
        }
        B = l; K -= B * (B + 1) / 2;

        l = 0; r = N;
        while(l != r - 1) {
            temp = mid = (l + r) / 2;
            temp = temp;
            if(temp > K) r = mid;
            else l = mid;
        }
        C = l; K -= C;

        cout << N - 2 - A << " " << N - 1 - B << " " << N - C << endl;
    }
}
