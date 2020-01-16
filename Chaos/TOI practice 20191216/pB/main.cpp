#include <iostream>
#include <memory.h>

using namespace std;
const int MAXN = 5e2;
bool conn[MAXN][MAXN];
int main() {
    int N ,M ,Q ,src ,dst ,i ,j ,k;
    while(cin >> N >> M >> Q) {
        memset(conn ,0 ,sizeof(conn));
        while(M--) {
            cin >> src >> dst;
            conn[src][dst] = true;
        }
        for(k = 0;k < N;k++) for(i = 0;i < N;i++) for(j = 0;j < N;j++) conn[i][j] |= (conn[i][k] && conn[k][j]);
        while(Q--) {
            cin >> src >> dst;
            cout << (conn[src][dst] ? "YES" : "NO") << endl;
        }
    }
}
