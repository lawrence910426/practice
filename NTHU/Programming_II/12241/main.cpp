#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;
const long long mod = 1e9 + 7;

class Matrix {
public:
    long long data[2][2] = {{1, 0}, {0, 1}}, temp[2][2];    

    Matrix() {}
    void Mul(Matrix* m) {
        memset(temp, 0, sizeof(temp));
        for(int i = 0;i < 2;i++) for(int j = 0;j < 2;j++) for(int k = 0;k < 2;k++) temp[i][j] = (temp[i][j] + (data[i][k] * m->data[k][j]) % mod) % mod;
        swap(temp, data);
    }
    void Pow(long long N) {
        Matrix ans = Matrix();
        while(N > 0) {
            if(N & 1) ans.Mul(this);
            this->Mul(this);
            N >>= 1;
        }
        swap(this->data, ans.data);
    }
};

int main() {
    long long N;
    while(cin >> N) {
        if(N == 1) {
            cout << 1 << endl;
        } else if(N == 2) {
            cout << 1 << endl;
        } else {
            Matrix transfer = Matrix();
            transfer.data[0][0] = transfer.data[0][1] = transfer.data[1][0] = 1;
            transfer.data[1][1] = 0;
            transfer.Pow(N - 2);
            cout << (transfer.data[0][0] + transfer.data[0][1]) % mod << endl;
        }
    }   
}
