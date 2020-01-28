#include <iostream>

using namespace std;
const long long mod = 1e9 + 7;
int main() {
    long long a = 0 ,b = 1 ,c = 1 ,A ,B ,C ,K;
    cin >> K;
    while(K--) {
        A = -b;
        B = -(a + b);
        C = (A + B);
        while(A < 0) A = (A + mod) % mod;
        while(B < 0) B = (B + mod) % mod;
        while(C < 0) C = (C + mod) % mod;
        a = A;
        b = B;
        c = C;
        //system("pause");
    }
    cout << a << " " << b << " " << c << endl;
}
