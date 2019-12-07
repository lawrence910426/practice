#include <iostream>
#include <time.h>
#include <random>
using namespace std;
const int MAXN = 2e3 + 10;
int data[MAXN][MAXN] ,N ,Q;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    srand(time(0));
    int i ,j ,l ,r ,u ,d ,target ,cnt ,ans;
    while(cin >> N ,N) {
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) cin >> data[i][j];
        for(cin >> Q;Q--;) {
            cin >> l >> r >> u >> d;
            long long start = clock() ,times = 0;
            ans = -1;
            while(ans == -1 && times < 1500 && clock() - start < 1e4) {
                target = data[rand() % (r - l + 1) + l][rand() % (d - u + 1) + u];
                //cout << target << endl;
                cnt = 0;
                for(i = l;i <= r;i++) for(j = u;j <= d;j++) if(target == data[i][j]) cnt += 1;
                if(cnt * 2 > (r - l + 1) * (d - u + 1)) ans = target;
            }
            cout << ans << '\n';
        }
    }
}
