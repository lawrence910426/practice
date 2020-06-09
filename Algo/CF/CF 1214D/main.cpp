#include <iostream>
#include <map>
#include <memory.h>

using namespace std;
bool obstacle[1000005] ,visit[1000005];
int N ,M;

bool dfs(int x ,int y) {
    if(visit[x * M + y] || obstacle[x * M + y]) return false;
    visit[x * M + y] = true;
    if(x == N - 1 && y == M - 1) return true;
    if(x == N - 1 && dfs(x ,y + 1)) return true;
    if(y == M - 1 && dfs(x + 1 ,y)) return true;
    return dfs(x ,y + 1) || dfs(x + 1 ,y);
}

int main() {
    int i ,j;
    char eax;
    bool result;
    while(cin >> N >> M) {
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) {
            cin >> eax;
            obstacle[i * M + j] = (eax == '#');
        }

        memset(visit ,0 ,sizeof(visit));
        result = dfs(0 ,0);
        visit[0] = visit[N * M - 1] = false;
        /*for(i = 0;i < N;i++) {
            for(j = 0;j < M;j++) {
                if(obstacle[i * M + j]) cout << '#';
                else if(visit[i * M + j]) cout << '@';
                else cout << '.';
            }
            cout << endl;
        }*/
        if(result) {
            result = dfs(0 ,0);
            visit[0] = visit[N * M - 1] = false;
            /*for(i = 0;i < N;i++) {
                for(j = 0;j < M;j++) {
                    if(obstacle[i * M + j]) cout << '#';
                    else if(visit[i * M + j]) cout << '@';
                    else cout << '.';
                }
                cout << endl;
            }*/
            if(result) cout << 2 << endl;
            else cout << 1 << endl;
        } else cout << 0 << endl;;
    }
}
