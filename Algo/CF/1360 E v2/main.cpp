#include <iostream>
#include <memory.h>

using namespace std;
bool raw[100][100];

int main() {
    int T, N; char eax; int i, j; bool able;
    for(cin >> T;T--;) {
        cin >> N; memset(raw, 0, sizeof(raw)); able = true;
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) { cin >> eax; raw[i][j] = (eax == '1'); }
        for(i = 0;i <= N;i++) raw[i][N] = raw[N][i] = true;
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) if(raw[i][j]) able &= (raw[i][j + 1] || raw[i + 1][j]);
        cout << (able ? "YES" : "NO") << endl;
    }
}
