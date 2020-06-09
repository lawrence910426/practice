#include <iostream>
#include <vector>
#include <memory.h>
#include <bitset>
#include <set>

using namespace std;
const int MAXN = 300 ,INF = (1LL << 31) - 1;
int dist[MAXN][MAXN] ,weight[MAXN] ,N ,K;
vector<int> G[MAXN];
bitset<MAXN> toggle;
int brute(int on) {
    if(on == N) return 0;
    int result_on = 0 ,result_off = 0;
    bool can_on = true;
    for(int i = 0;i < N;i++) if(toggle[i] && dist[i][on] <= K) can_on = false;
    if(can_on) {
        toggle[on] = true;
        result_on = brute(on + 1) + weight[on];
    }
    toggle[on] = false;
    result_off = brute(on + 1);
    return max(result_on ,result_off);
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,j ,k ,eax ,ebx;
    while(cin >> N >> K) {
        for(i = 0;i < MAXN;i++) G[i].clear();
        for(i = 0;i < MAXN;i++) for(j = 0;j < MAXN;j++) dist[i][j] = INF;
        for(i = 0;i < N;i++) cin >> weight[i];
        for(i = 0;i < N - 1;i++) {
            cin >> eax >> ebx;
            eax -= 1 ,ebx -= 1;
            G[eax].push_back(ebx);
            G[ebx].push_back(eax);
            dist[eax][ebx] = dist[ebx][eax] = 1;
        }
        for(k = 0;k < N;k++) for(i = 0;i < N;i++) for(j = 0;j < N;j++) if(dist[i][k] != INF && dist[k][j] != INF) dist[i][j] = min(dist[i][j] ,dist[i][k] + dist[k][j]);
        toggle.reset();
        cout << brute(0) << endl;
    }
}
