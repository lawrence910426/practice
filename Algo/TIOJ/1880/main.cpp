#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
const int MAXN = 1e5 + 50 ,MOD = 1e6 + 7;

vector<int> G[MAXN];
bitset<MAXN> visit ,color;
bool dfs(int on ,bool style) {
    if(visit[on]) {
        if(color[on] != style) return false;
        return true;
    } else {
        visit[on] = true;
        color[on] = style;
    }
    for(int V : G[on]) if(dfs(V ,!style) == false) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,M;
    int i ,src ,dst;
    long long ans;
    bool first = true;

    cin >> N >> M;
    while(M--) {
        cin >> src >> dst;
        G[src].push_back(dst);
        G[dst].push_back(src);
    }
    for(i = 1;i <= N;i++) {
        if(visit[i]) continue;
        if(dfs(i ,true)) {
            if(first) {
                ans = 1;
                first = false;
            } else {
                ans <<= 1;
                ans %= MOD;
            }
        } else ans = 0;
    }
    cout << ans << endl;
}
