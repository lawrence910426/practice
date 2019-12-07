#include <iostream>
#include <random>
#include <time.h>
#include <assert.h>

using namespace std;
const int MAXN = 2e3 + 5;
int data[MAXN][MAXN] ,N ,Q ,ans ,target;
int main() {
    srand(0);
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int l ,r ,u ,d ,x ,y;
    int i ,j ,counts;
    while(cin >> N ,N) {
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) cin >> data[i][j];
        for(cin >> Q;Q--;) {
            cin >> l >> r >> u >> d;
            ans = -1;
            for(double stamp = clock();ans == -1 && clock() - stamp < 1e5;) {
                x = rand() % (r - l + 1) + l ,y = rand() % (d - u + 1) + u;
                if(0 <= x && x < N) ; else return -1;
                if(0 <= y && y < N) ; else return -1;
                target = data[x][y];
                counts = 0;
                for(i = l;i <= r;i++) for(j = u;j <= d;j++) if(data[i][j] == target) counts += 1;
                if(counts * 2 > (r - l + 1) * (d - u + 1)) ans = target;
            }
            cout << ans << '\n';
        }
    }
}
