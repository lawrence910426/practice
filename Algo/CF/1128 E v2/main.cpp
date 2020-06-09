#include <iostream>
#include <memory.h>

using namespace std;
const long long MatMod = 1e9 + 6, Mod = 1e9 + 7;
class Matrix {
public:
    long long data[5][5], temp[5][5];
    Matrix() { memset(data, 0, sizeof(data)); }
    void Multiply(Matrix* M) {
        int i, j, k; memset(temp, 0, sizeof(temp));
        for(i = 0;i < 5;i++) for(j = 0;j < 5;j++) for(k = 0;k < 5;k++) { temp[i][j] += this->data[i][k] * M->data[k][j]; temp[i][j] %= MatMod; }
        memcpy(this->data, this->temp, sizeof(this->data));
    }
    void Pow(long long power) {
        Matrix *temp = this, *ans = new Matrix();
        ans->data[0][0] = ans->data[1][1] = ans->data[2][2] = ans->data[3][3] = ans->data[4][4] = 1;
        while(power > 0) {
            if(power % 2 == 1) ans->Multiply(temp);
            temp->Multiply(temp);
            power >>= 1;
        }
        memcpy(this->data, ans->data, sizeof(this->data));
        delete ans;
    }
};

long long pow(long long base, long long power) {
    long long ans = 1, temp = base;
    while(power > 0) {
        if(power % 2 == 1) { ans *= temp; ans %= Mod; }
        temp *= temp; temp %= Mod;
        power >>= 1;
    }
    return ans;
}

int main() {
    long long n, f1, f2, f3, c, ans = 1; cin >> n >> f1 >> f2 >> f3 >> c;
    Matrix *F = new Matrix(), *D = new Matrix(); F->data[0][2] = F->data[1][0] = F->data[1][2] = F->data[2][1] = F->data[2][2] = 1;
    D->data[0][1] = D->data[1][2] = D->data[2][0] = D->data[2][1] = D->data[2][2] = D->data[2][3] = D->data[3][3] = D->data[3][4] = D->data[4][4] = 1;
    Matrix *f = new Matrix(), *d = new Matrix(); f->data[0][0] = f->data[1][0] = f->data[2][0] = 1; d->data[3][0] = d->data[4][0] = 1;
    F->Pow(n - 4); D->Pow(n - 3); F->Multiply(f); D->Multiply(d);
    ans *= pow(f1, F->data[0][0]); ans %= Mod;
    ans *= pow(f2, F->data[1][0]); ans %= Mod;
    ans *= pow(f3, F->data[2][0]); ans %= Mod;
    ans *= pow((c * c) % Mod, D->data[2][0]); ans %= Mod;
    cout << ans << endl;
}
