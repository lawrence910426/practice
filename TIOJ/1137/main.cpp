#include <iostream>
#include <vector>
#include <bitset>
#include <memory.h>

using namespace std;
const int MAXN = 1e4 + 50;
vector<int> G[MAXN];
int T ,N ,M;
bitset<MAXN> visit;
bitset<MAXN> cut;
int dfs_n[MAXN] ,low[MAXN] ,dfs_t;
void dfs(int on ,int parent) {
    visit[on] = true;
    int son = 0;
    dfs_n[on] = low[on] = dfs_t++;
    for(int V : G[on]) {
        if(!visit[V]) {
            son += 1;
            dfs(V ,on);
            if(low[V] >= dfs_n[on]) {
                if(parent != -1)
                    cut[on] = true;
            } else low[on] = min(low[on] ,low[V]);
        } else if(dfs_n[V] < dfs_n[on] && V != parent) {
            low[on] = min(dfs_n[V] ,low[on]);
        }
    }
    if(parent == -1 && son > 1) cut[on] = true;
}

int main() {
    int i ,src ,dst;
    for(cin >> T;T--;) {
        cin >> N >> M;
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        while(M--) {
            cin >> src >> dst;
            G[src].push_back(dst);
            G[dst].push_back(src);
        }
        visit.reset();
        cut.reset();
        dfs_t = 0;
        memset(dfs_n ,0 ,sizeof(dfs_n));
        memset(low ,0 ,sizeof(low));
        for(i = 1;i <= N;i++) if(!visit[i]) dfs(i ,-1);
        vector<int> cuts;
        for(i = 1;i <= N;i++) if(cut[i]) cuts.push_back(i);
        cout << cuts.size() << endl;
        if(cuts.size() == 0) cout << 0;
        else for(int C : cuts) cout << C << " ";
        cout << endl;
    }
}
