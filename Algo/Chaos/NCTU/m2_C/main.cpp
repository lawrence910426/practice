#include <iostream>
#include <memory.h>
using namespace std;

long long M = 1e9 + 7;

class Matrix {
public:
    long long data[3][3], temp[3][3];
    Matrix() { memset(data, 0, sizeof(data)); }
    void Multiply(Matrix* Mat) {
        int i, j, k;
        for(i = 0;i < 3;i++) for(j = 0;j < 3;j++) temp[i][j] = 0;
        for(i = 0;i < 3;i++) for(j = 0;j < 3;j++) for(k = 0;k < 3;k++) { temp[i][j] += (data[i][k] * Mat->data[k][j]) % M; temp[i][j] %= M; }
        for(i = 0;i < 3;i++) for(j = 0;j < 3;j++) data[i][j] = temp[i][j];
    }
    void Power(long long power) {
        Matrix *temp = new Matrix();
        int i, j;
        for(i = 0;i < 3;i++) for(j = 0;j < 3;j++) temp->data[i][j] = this->data[i][j];
        for(i = 0;i < 3;i++) this->data[i][i] = 1;
        while(power > 0) {
            if(power % 2 == 1) this->Multiply(temp);
            temp->Multiply(temp);
            power >>= 1;
        }
    }
} *Transfer, *Ans;

int main() {
    int T;
    long long X, N;
    for(cin >> T;T--;) {
        cin >> X >> N >> M;
        Transfer = new Matrix(); Ans = new Matrix();
        Transfer->data[0][0] = Transfer->data[0][1] = 1;
        Transfer->data[1][1] = Transfer->data[1][2] = Transfer->data[2][2] = X;
        Ans->data[1][0] = Ans->data[2][0] = X;
        Transfer->Power(N - 1); Transfer->Multiply(Ans);
        cout << Transfer->data[0][0] << endl;
    }
}
