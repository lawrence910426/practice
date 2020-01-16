#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
const int MAXN = 1e5 + 50;
vector<int> G[MAXN];
int N ,M;
bitset<MAXN> visit ,color;
pair<int ,int> dfs(int on ,bool c) {
    visit[on] = true;
    color[on] = c;
    pair<int ,int> ans = pair<int ,int>(0 ,0);
    if(color[on]) ans.first += 1;
    else ans.second += 1;

    for(int V : G[on]) {
        if(visit[V]) {
            if(color[V] == c) return pair<int ,int>(-1 ,-1);
        } else {
            pair<int ,int> tmp = dfs(V ,!c);
            if(tmp.first == -1 && tmp.second == -1) return tmp;
            else {
                ans.first += tmp.first;
                ans.second += tmp.second;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,M ,ans;
    int i ,src ,dst;
    while(cin >> N >> M) {
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        for(i = 0;i < M;i++) {
            cin >> src >> dst;
            G[src].push_back(dst);
            G[dst].push_back(src);
        }
        visit.reset() ,color.reset() ,ans = 0;
        for(i = 1;i <= N;i++) if(!visit[i]) {
            pair<int ,int> ret = dfs(i ,true);
            if(ret.first == -1 && ret.second == -1) {
                cout << 0 << '\n';
                break;
            } else ans += min(ret.first ,ret.second);
        }
        if(i == N + 1) cout << ans << '\n';
    }
}
