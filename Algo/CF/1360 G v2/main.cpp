#include <iostream>
#include <memory.h>

using namespace std;
bool ans[50][50];
int main() {
    int T, N, M, A, B, sum; int i, j; bool good;
    for(cin >> T;T--;) {
        cin >> N >> M >> A >> B;
        memset(ans, 0, sizeof(ans));
        for(j = 0;j < A;j++) ans[0][j] = true;
        for(i = 1;i < N;i++) for(j = 0;j < M;j++) ans[i][(j + A) % M] = ans[i - 1][j];

        good = true;
        for(i = 0;i < N;i++) {
            sum = 0;
            for(j = 0;j < M;j++) if(ans[i][j]) sum += 1;
            good &= (sum == A);
        }
        for(j = 0;j < M;j++) {
            sum = 0;
            for(i = 0;i < N;i++) if(ans[i][j]) sum += 1;
            good &= (sum == B);
        }

        if(good) {
            cout << "YES" << endl;
            for(i = 0;i < N;i++) {
                for(j = 0;j < M;j++) cout << ans[i][j];
                cout << endl;
            }
        } else cout << "NO" << endl;
    }
}
