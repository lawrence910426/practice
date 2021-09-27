#include <iostream>
#include <memory.h>
#include <queue>

using namespace std;

const int MAXN = 1e3 + 50;
char mapa[MAXN][MAXN];
bool visit[MAXN][MAXN];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

struct status { int x, y, time; };

int N, M, ans = 0, remain = 0;

int main() {
    memset(mapa, 0, sizeof(mapa)); 
    memset(visit, 0, sizeof(visit));
    int i, j, k;

    cin >> N >> M;
    for(i = 0;i < N;i++) for(j = 0;j < M;j++) cin >> mapa[i][j];
    for(i = 0;i < N;i++) for(j = 0;j < M;j++) remain += (mapa[i][j] == 'T' ? 1 : 0); 
    for(i = 0;i < N;i++) for(j = 0;j < M;j++) if(mapa[i][j] == 'I') goto bfs;

bfs:
    queue<status> Q;
    for(Q.push({i, j, 0});remain > 0 && !Q.empty();Q.pop()) {
        if(Q.front().x < 0 || N <= Q.front().x || Q.front().y < 0 || M <= Q.front().y) continue;
        if(visit[Q.front().x][Q.front().y] || mapa[Q.front().x][Q.front().y] == 'C') continue;
        visit[Q.front().x][Q.front().y] = true;
        if(mapa[Q.front().x][Q.front().y] == 'T') remain -= 1;
        ans = max(ans, Q.front().time);
        for(k = 0;k < 4;k++) Q.push({Q.front().x + dx[k], Q.front().y + dy[k], Q.front().time + 1});
    }
    cout << (remain == 0 ? ans : -1) << endl;
}
