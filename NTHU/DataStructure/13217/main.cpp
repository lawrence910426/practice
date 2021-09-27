#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > floyd = vector<vector<int> >(100, vector<int>(100, 0));

int main() {
    int T, t, N, Q, a, b;
    cin >> T;
    for(t = 1;t <= T;t++) {
        cin >> N >> Q;
        for(int i = 0;i < N;i++) for(int j = 0;j < N;j++) {
            cin >> floyd[i][j];
            if(floyd[i][j] == 0) floyd[i][j] = 20 * 100 * 100 + 1;
        }
        for(int k = 0;k < N;k++) for(int i = 0;i < N;i++) for(int j = 0;j < N;j++)
            floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);
        cout << "Testcase" << t << endl;
        while(Q--) {
            cin >> a >> b;
            cout << "Cost(" << a << "," << b << "):";
            if(floyd[a][b] == 20 * 100 * 100 + 1) cout << "No Service" << endl;
            else cout << floyd[a][b] << endl;
        }
    }
}
