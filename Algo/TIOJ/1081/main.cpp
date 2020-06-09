#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <memory.h>
using namespace std;

bool data[1005][1005];
int n, m ,dsu[1020100] ,dx[8] = {-1 ,-1 ,-1 ,0 ,1 ,1, 1, 0} ,dy[8] = {-1 ,0 ,1 ,1 ,1 ,0 ,-1 ,-1};
inline int codec(int x ,int y) { return x * m + y; }
int boss(int x) { return (dsu[x] == -1 ? x : dsu[x] = boss(dsu[x])); }
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    register int i, j ,k;
    int sum ,a ,b ,x ,y;
    register char c;
    while(cin >> n >> m ,n) {
        memset(dsu ,-1 ,sizeof(dsu));
        memset(data ,0 ,sizeof(data));
        sum = 0;
        for(i = 1;i <= n;i++) for(j = 1;j <= m;j++) {
            cin >> c;
            if(c == '1') {
                sum += 1;
                data[i][j] = true;
            }
        }
        for(i = 1;i <= n;i++) for(j = 1;j <= m;j++) if(data[i][j]) for(k = 0;k < 8;k++) {
            x = i + dx[k] ,y = j + dy[k];
            data[i][j] = false;
            if(data[x][y]) {
                a = codec(x ,y);
                b = codec(i ,j);
                a = boss(a) ,b = boss(b);
                if(a != b) {
                    dsu[a] = b;
                    sum -= 1;
                }
            }
        }
        cout << sum << '\n';
    }
}
