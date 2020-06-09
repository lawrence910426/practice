#include <iostream>

using namespace std;

int main() {
    int a = 0 ,b = 1 ,c = 1 ,A ,B ,C;
    while(true) {
        A = -b;
        B = -(a + b);
        C = (A + B);
        cout << A << " " << B << " " << C << endl;
        a = A;
        b = B;
        c = C;
        system("pause");
    }
}
