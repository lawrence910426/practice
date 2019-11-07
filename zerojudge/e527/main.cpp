#pragma GCC optimize("Ofast")
#include <iostream>
#include <memory.h>
using namespace std;
int possible[3000] ,N ,x ,y ,target;
int best[3000][3000];
void dfs(int now_x ,int now_y ,int depth) {
    bool alive = false;
    if(possible[now_x] == -1 || possible[now_x] >= depth) possible[now_x] = depth;
    if(possible[now_y] == -1 || possible[now_y] >= depth) possible[now_y] = depth;
    if(best[now_x][now_y] == -1 || best[now_x][now_y] > depth) alive = true ,best[now_x][now_y] = depth;
    if(!alive) return;
    dfs(0 ,now_y ,depth + 1);
    dfs(now_x ,0 ,depth + 1);
    dfs(x ,now_y ,depth + 1);
    dfs(now_x ,y ,depth + 1);
    if(now_x + now_y <= y) dfs(0 ,now_x + now_y ,depth + 1);
    else dfs(now_x + now_y - y ,y ,depth + 1);
    if(now_x + now_y <= x) dfs(now_x + now_y ,0 ,depth + 1);
    else dfs(x ,now_x + now_y - x ,depth + 1);
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    for(cin >> N;N--;) {
        memset(possible ,-1 ,sizeof(possible));
        memset(best ,-1 ,sizeof(best));
        cin >> x >> y >> target;
        dfs(0 ,0 ,0);
        cout << possible[target] << endl;
    }
}
