#include <iostream>
#include <bitset>
#include <memory.h>
#include <vector>
#include <stack>
#include <set>

using namespace std;
const int MAXN = 1005;

bitset<MAXN> graph[MAXN];
vector<int> G[MAXN];
bitset<MAXN> articular;
bitset<MAXN> visit;
int low[MAXN] ,dfn[MAXN] ,dft ,nbcc;
stack<int> stk;
set<int> bcc[MAXN];
bitset<MAXN> color;
bitset<MAXN> odd;

void dfs(int on ,int parent) {
    visit[on] = true;
    low[on] = dfn[on] = dft++;
    int son = 0;
    stk.push(on);
    for(int V : G[on]) {
        if(!visit[V]) {
            son += 1;
            dfs(V ,on);
            if(low[V] >= dfn[on]) {
                if(parent != -1) articular[on] = true;
                for(int x = 0;x != V;stk.pop()) x = stk.top() ,bcc[nbcc].insert(x);
                bcc[nbcc++].insert(on);
            } else {
                low[on] = min(low[on] ,low[V]);
            }
        } else if(V != parent && dfn[V] < dfn[on]) {
            low[on] = min(low[on] ,dfn[V]);
        }
    }
    if(parent == -1 && son > 1) articular[on] = true;
}

bool draw(int on ,int code ,bool col) {
    if(bcc[code].find(on) == bcc[code].end()) return false;
    if(visit[on]) return odd[on] = (color[on] != col);
    visit[on] = true;
    color[on] = col;
    bool result = false;
    for(int V : G[on]) result |= draw(V ,code ,!col);
    odd[on] = result;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,M ,src ,dst ,ans;
    int i ,j;
    while(cin >> N >> M ,!(N == 0 && M == 0)) {
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        for(i = 0;i < MAXN;i++) graph[i].reset();
        for(i = 0;i < MAXN;i++) bcc[i] = set<int>();
        nbcc = ans = dft = 0;
        memset(low ,0 ,sizeof(low)), memset(dfn ,0 ,sizeof(dfn));
        articular.reset(), visit.reset();
        while(M--) {
            cin >> src >> dst;
            graph[src][dst] = graph[dst][src] = true;
        }
        for(i = 1;i <= N;i++) for(j = 1;j <= N;j++) if(!graph[i][j]) G[i].push_back(j);
        for(i = 1;i <= N;i++) if(!visit[i]) dfs(i ,-1);
        for(i = 0;i < nbcc;i++) {
            cout << "The cut vertex:" << endl;
            for(int V : bcc[i]) cout << V << " ";
            cout << endl;
            visit.reset(), color.reset(), odd.reset();
            draw(*bcc[i].begin() ,i ,true);
            for(int V : bcc[i]) if(!odd[V]) ans += 1;
        }
        cout << ans << endl;
    }
}
