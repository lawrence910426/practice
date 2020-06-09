#include <iostream>
#include <memory.h>
using namespace std;
const int MAXN = 3e5 + 50 ,MAXM = 10 ,SIZ = (1 << 10) ,INF = (1LL << 30);
int N ,M;
int data[MAXN][MAXM] ,status[SIZ];
int main() {
    int L ,R ,mid ,value ,ans_a ,ans_b ,ans;
    bool able;
    int i ,j;
    while(cin >> N >> M) {
        ans = ans_a = ans_b = -1;
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) cin >> data[i][j];
        for(L = 0, R = INF;L != R - 1;) {
            mid = (L + R) >> 1;
            able = false;
            memset(status ,-1 ,sizeof(status));
            for(i = 0;i < N;i++) {
                for(value = j = 0;j < M;j++) value |= (data[i][j] >= mid ? 1 : 0) << j;
                status[value] = i + 1;
            }
            for(i = 0;i < (1 << M);i++) for(j = 0;j < (1 << M);j++) {
                if(i | j == (1 << M) - 1) if(status[i] != -1 && status[j] != -1) {
                    if(ans < mid) {
                        ans_a = status[i];
                        ans_b = status[j];
                    }
                    able = true;
                    break;
                }
            }
            if(able) L = mid;
            else R = mid;
        }
        cout << ans_a << " " << ans_b << endl;
    }
}
