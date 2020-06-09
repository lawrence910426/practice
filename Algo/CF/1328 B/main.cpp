#include <iostream>

using namespace std;

const int MAXN = 1e5 + 50;
int T;
long long N ,K ,l ,r ,mid ,temp ,A ,B;
int main() {
    int i;
    for(cin >> T;T--;) {
        cin >> N >> K; K -= 1;
        l = 1; r = N;
        while(l != r - 1) {
            mid = (l + r) / 2;
            temp = (mid - 1) * mid / 2;
            if(temp > K) r = mid;
            if(temp < K) l = mid;
            if(temp == K) { l = mid; break; }
        }
        A = l; B = K - A * (A - 1) / 2;
        for(i = N - 1;i >= 0;i--) cout << (i == A || i == B ? "b" : "a");
        cout << endl;
    }
}
