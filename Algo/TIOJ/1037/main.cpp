#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <memory.h>
using namespace std;

bool previous[105][105] ,current[105][105];
int N ,M ,x1 ,y1 ,x2 ,y2 ,K ,D;
inline int modulo(int val ,int mod) {
    if(val >= 0) return val % mod;
    else return (val % mod) + mod;
}

void show() {
    for(int i = 0;i < N;cout << endl ,i++) for(int j = 0;j < M;j++) cout << (current[i][j] ? '#' : '.');
    cout << endl;
}

int main() {
    int i ,j;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N >> M >> x1 >> y1 >> x2 >> y2) {
        memset(previous ,0 ,sizeof(previous));
        memset(current ,0 ,sizeof(current));
        current[x1][y1] = true;
        //show();
        for(cin >> K;K--;) {
            cin >> D;
            memset(previous ,0 ,sizeof(previous));
            for(i = 0;i < N;i++) for(j = 0;j < M;j++) if(current[i][j]) {
                previous[i][modulo(j + D ,M)] = previous[i][modulo(j - D ,M)] = true;
                previous[modulo(i + D ,N)][j] = previous[modulo(i - D ,N)][j] = true;
            }
            memcpy(current ,previous ,sizeof(previous));
            //show();
        }
        cout << (previous[x2][y2] ? "YES" : "NO") << endl;
    }
}
