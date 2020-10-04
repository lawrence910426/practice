#include <iostream>
#include <memory.h>

using namespace std;
const int MAXN = 20;
int mapa[MAXN][MAXN];
bool placed[MAXN][MAXN];
/* 0: unused, -1 or less: used */

int N, M;

int dfs(int row, int queens, int rocks) {
    int ans = 0;
    if(queens < 0 || rocks < 0) return ans;
    if(row == N + M - 1) {
        for(int i = 0;i < N + M;i++) if(mapa[row][i] == 0) {
            if(queens == 1) {
                bool able = true;
                for(int j = 0;row - j >= 0 && i - j >= 0;j++) able &= (placed[row - j][i - j] == false);
                for(int j = 0;row - j >= 0 && i + j < N + M;j++) able &= (placed[row - j][i + j] == false);
                ans += (able ? 1 : 0);
            } else if(rocks == 1) { ans += 1; }
        }
    } else {
        for(int i = 0;i < N + M;i++) if(mapa[row][i] == 0) {
            /* Queen */
            bool able = true;
            for(int j = 0;row - j >= 0 && i - j >= 0;j++) able &= (placed[row - j][i - j] == false);
            for(int j = 0;row - j >= 0 && i + j < N + M;j++) able &= (placed[row - j][i + j] == false);
            if(able) {
                for(int j = 0;row + j < N + M;j++) mapa[row + j][i] -= 1;
                for(int j = 0;row + j < N + M && i + j < N + M;j++) mapa[row + j][i + j] -= 1;
                for(int j = 0;row + j < N + M && i - j >= 0;j++) mapa[row + j][i - j] -= 1;
                placed[row][i] = true;
                ans += dfs(row + 1, queens - 1, rocks);
                placed[row][i] = false;
                for(int j = 0;row + j < N + M;j++) mapa[row + j][i] += 1;
                for(int j = 0;row + j < N + M && i + j < N + M;j++) mapa[row + j][i + j] += 1;
                for(int j = 0;row + j < N + M && i - j >= 0;j++) mapa[row + j][i - j] += 1;
            }

            /* Rock */
            for(int j = 0;row + j < N + M;j++) mapa[row + j][i] -= 1;
            placed[row][i] = true;
            ans += dfs(row + 1, queens, rocks - 1);
            placed[row][i] = false;
            for(int j = 0;row + j < N + M;j++) mapa[row + j][i] += 1;
        }
    }

    return ans;
}

int main() {
    cin >> N >> M;
    cout << dfs(0, N, M) << endl;
}
