#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
const int MAXN = 2005;

vector<int> G[MAXN];
pair<int ,int> E[500000];
int N ,M ,dis_src ,dis_dst ,ans;
bitset<MAXN> visit;
int dfs(int on) {
    if(visit[on]) return 0;
    visit[on] = true;
    int siz = 1;
    for(int V : G[on]) {
        if((on == dis_src && V == dis_dst) || (V == dis_src && on == dis_dst)) continue;
        siz += dfs(V);
    }
    return siz;
}
int main() {
    int i ,left ,right;
    while(cin >> N >> M) {
        for(i = 0;i < M;i++) {
            cin >> E[i].first >> E[i].second;
            G[E[i].first].push_back(E[i].second);
            G[E[i].second].push_back(E[i].first);
        }
        for(ans = i = 0;i < M;i++) {
            dis_src = E[i].first;
            dis_dst = E[i].second;
            visit.reset();
            left = dfs(E[i].first);
            if(visit[E[i].second]) continue;
            visit.reset();
            right = dfs(E[i].second);
            ans = max(ans ,left * right);
        }
        cout << ans << endl;
    }
}
/*
6 7
0 1
1 2
3 2
4 3
2 4
5 1
0 5
*/
