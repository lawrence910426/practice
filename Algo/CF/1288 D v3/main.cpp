#include <iostream>
#include <memory.h>

using namespace std;
const int MAXN = 3e5 + 50 ,MAXM = 10 ,SIZ = (1 << 10) ,INF = (1 << 30);
int N ,M ,L ,R ,mid ,ans_a ,ans_b;
int i ,j;
int data[MAXN][MAXM] ,status[SIZ];
bool check(int mid) {
    int value;
    memset(status ,-1 ,sizeof(status));
    for(i = 0;i < N;i++) {
        for(value = j = 0;j < M;j++) value |= (data[i][j] >= mid ? 1 : 0) << j;
        status[value] = i + 1;
    }
    for(i = 0;i < (1 << M);i++) for(j = 0;j < (1 << M);j++) if((i | j) == (1 << M) - 1 && status[i] != -1 && status[j] != -1) {
        ans_a = status[i];
        ans_b = status[j];
        return true;
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    while(cin >> N >> M) {
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) cin >> data[i][j];
        L = 0 ,R = INF;
        ans_a = ans_b = 1;
        while(L != R - 1) {
            mid = (L + R) / 2;
            if(check(mid)) L = mid;
            else R = mid;
        }
        cout << /*L << " " <<*/ ans_a << " " << ans_b << '\n';
    }
}
