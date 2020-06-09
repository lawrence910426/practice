#include <iostream>

using namespace std;

char matrix[30][30];
int main() {
    int T, N, M, diff; int i, j; bool same;
    for(cin >> T;T--;) {
        cin >> N >> M;
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) cin >> matrix[i][j];
        for(diff = j = 0;j < M;j++) {
            same = true;
            for(i = 1;i < N;i++) same &= (matrix[i - 1][j] == matrix[i][j]);
            diff += (same ? 0 : 1);
        }
        if(diff > 2) cout << -1 << endl;
        else {
            for(j = 0;j < M;j++) cout << matrix[0][j];
            cout << endl;
        }
    }
}
