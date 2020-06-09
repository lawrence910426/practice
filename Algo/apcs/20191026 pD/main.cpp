#include <iostream>
#include <queue>

using namespace std;
const int MAXN = 30 ,INF = (1LL << 31) - 1;
bool matrix[MAXN][MAXN];
int N ,M ,dp[MAXN][MAXN][MAXN][MAXN] ,ans;
struct Area {
    int L ,R ,U ,D;
    Area(): L(0) ,R(0) ,U(0) ,D(0) {}
    Area(int l ,int r ,int u ,int d): L(l) ,R(r) ,U(u) ,D(d) {}
    Area operator+ (const Area& a) { return Area(L + a.L ,R + a.R ,U + a.U ,D + a.D); }
    int* getdp() { return &dp[L][R][U][D]; }
};
queue<Area> Q;

void update(Area now ,int type) {
    int i ,fs = 0 ,ts = 0 ,delta;
    Area next;
    if(type == 1) {
        for(i = now.U;i < now.D;i++) if(matrix[now.L][i]) ts += 1; else fs += 1;
        next = now + Area(1 ,0 ,0 ,0);
    } else if(type == 2) {
        for(i = now.U;i < now.D;i++) if(matrix[now.R - 1][i]) ts += 1; else fs += 1;
        next = now + Area(0 ,-1 ,0 ,0);
    } else if(type == 3) {
        for(i = now.L;i < now.R;i++) if(matrix[i][now.U]) ts += 1; else fs += 1;
        next = now + Area(0 ,0 ,1 ,0);
    } else {
        for(i = now.L;i < now.R;i++) if(matrix[i][now.D - 1]) ts += 1; else fs += 1;
        next = now + Area(0 ,0 ,0 ,-1);
    }
    if(*next.getdp() > *now.getdp() + min(ts ,fs)) {
        *next.getdp() = *now.getdp() + min(ts ,fs);
        Q.push(next);
    }
}

int main() {
    int i ,j ,k ,z ,eax;
    while(cin >> N >> M) {
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) cin >> eax ,matrix[i][j] = eax == 1;
        for(i = 0;i < N;i++) for(j = 0;j <= N;j++) for(k = 0;k < M;k++) for(z = 0;z <= M;z++) dp[i][j][k][z] = INF;
        dp[0][N][0][M] = 0, ans = INF ,Q = queue<Area>();
        for(Q.push(Area(0 ,N ,0 ,M));!Q.empty();Q.pop()) {
            Area now = Q.front();
            if(now.L == now.R - 1 && now.U == now.D - 1) ans = min(ans ,*now.getdp());
            if(now.L == now.R - 1 && now.U != now.D - 1) update(now ,3), update(now ,4);
            if(now.L != now.R - 1 && now.U == now.D - 1) update(now ,1), update(now ,2);
            if(now.L != now.R - 1 && now.U != now.D - 1) update(now ,1), update(now ,2) ,update(now ,3) ,update(now ,4);
        }
        cout << ans << endl;
    }
}
