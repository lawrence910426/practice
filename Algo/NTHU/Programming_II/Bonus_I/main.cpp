#include <iostream>
#include <memory.h>
using namespace std;

struct Matrix {
    long long A[2][2], temp[2][2];
    void Mul(Matrix& m) {
        memset(temp, 0, sizeof(temp));
        for(int i = 0;i < 2;i++) for(int j = 0;j < 2;j++) for(int k = 0;k < 2;k++) temp[i][j] += A[i][k] * m.A[k][j];
        swap(temp, A);
    }
};

int main() {
    long long Q, ans, x;
    Matrix trans, M;
    trans.A[0][0] = 1;
    trans.A[0][1] = trans.A[1][0] = 1;
    trans.A[1][1] = 0;
    while(cin >> Q) {
        M.A[0][0] = M.A[1][1] = 1;
        M.A[0][1] = M.A[1][0] = 0;
        ans = 2e18;
        while(M.A[0][0] < 1e18 && M.A[0][1] < 1e18 && M.A[1][0] < 1e18 && M.A[1][1] < 1e18) {  
            M.Mul(trans);
            if((Q - M.A[0][1]) % M.A[0][0] != 0) continue;
            x = (Q - M.A[0][1]) / M.A[0][0];
            //cout << x << endl;
            ans = min(ans, max(0LL, x));
            //cout << M.A[0][0] << " " << M.A[0][1] << " " << M.A[1][0] << " " << M.A[1][1] << endl;
        }
        cout << ans << endl;
    }
}
