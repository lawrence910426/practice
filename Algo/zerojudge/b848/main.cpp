#pragma GCC optimize("Ofast")
#include <iostream>

using namespace std;
const long long mod = 1000007;
struct matrix {
    long long data[2][2];
    inline matrix operator* (matrix m) {
        matrix ret;
        ret.data[0][0] = ret.data[1][0] = ret.data[0][1] = ret.data[1][1] = 0;
        for(int i = 0;i < 2;i++) for(int j = 0;j < 2;j++) for(int k = 0;k < 2;k++) {
            ret.data[i][j] += data[i][k] * m.data[k][j];
            ret.data[i][j] %= mod;
        }
        return ret;
    }
    inline pair<long long ,long long> operator* (pair<long long ,long long> p) {
        long long alpha = p.first * data[0][0] + p.second * data[0][1];
        long long beta  = p.first * data[1][0] + p.second * data[1][1];
        return pair<long long ,long long>(alpha % mod ,beta % mod);
    }
};
matrix Male ,Female ,I;

inline matrix power(int K) {
    matrix ret = I ,tmp = Male;
    ret = I;
    for(;K != 0;K >>= 1) {
        if(K % 2 == 1) ret = ret * tmp;
        tmp = tmp * tmp;
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    Male.data[0][0] = 2;
    Male.data[0][1] = 1;
    Male.data[1][0] = 1;
    Male.data[1][1] = 0;
    Female.data[0][0] = 0;
    Female.data[0][1] = 3;
    Female.data[1][0] = 1;
    Female.data[1][1] = 0;
    I.data[0][0] = I.data[1][1] = 1;
    I.data[1][0] = I.data[0][1] = 0;
    int T ,N ,M ,K;
    pair<long long ,long long> p;
    for(cin >> T;T--;) {
        cin >> N >> M >> K;
        p = pair<long long ,long long>(N % mod ,M % mod);
        if(N < M) {
            p = Female * p;
            K -= 1;
        }
        p = power(K) * p;
        cout << p.first << " " << p.second << '\n';
    }
}
