#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <memory.h>
#include <climits>

#define MAXN 25
#define MAXNN 405
using namespace std;
int N ,Q ,NN ,x ,y ,xx, yy ,dx[4] = {0 ,0, -1, 1} ,dy[4] = {1 ,-1 ,0 ,0} ,floyd[MAXNN][MAXNN] ,raw[MAXN][MAXN] ,best;
int i ,j ,k ,l ,m ,tmp1 ,tmp2;

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N) {
        NN = N * N;
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) cin >> raw[i][j];
        for(i = 0;i < NN;i++) for(j = 0;j < NN;j++) floyd[i][j] = (1 << 15);
        for(i = 0;i < NN;i++) floyd[i][i] = 0;
        for(x = 0;x < N;x++) for(y = 0;y < N;y++) for(xx = 0;xx < N;xx++) for(yy = 0;yy < N;yy++) for(m = 0;m < 4;m++)
            if((x == dx[m] + xx && y == dy[m] + yy)) floyd[x * N + y][xx * N + yy] = raw[x][y] * (-1) + raw[xx][yy] * 2;
        for(k = 0;k < NN;k++) for(i = 0;i < NN;i++) for(j = 0;j < NN;j++) floyd[i][j] = min(floyd[i][j] ,floyd[i][k] + floyd[k][j]);
        for(cin >> Q;Q--;) {
            cin >> x >> y >> xx >> yy;
            x-- ,y-- ,xx-- ,yy--;
            best = INT_MAX;
            for(i = 0;i < N;i++) for(j = 0;j < N;j++) {
                tmp1 = floyd[x * N + y][i * N + j] + raw[x][y] * 2 + raw[i][j] * (-1);
                tmp2 = floyd[i * N + j][xx * N + yy] + raw[i][j] * 2 + raw[xx][yy] * (-1);
                best = min(best ,tmp1 + tmp2 - 2 * raw[i][j]);
            }
            cout << best << '\n';
        }
    }
}
/*
3
1 10 2
1 1 100
1 100 1
2
1 1 1 2
2 1 3 3
*/
