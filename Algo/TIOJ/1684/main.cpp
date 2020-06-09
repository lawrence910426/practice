#include <iostream>
#include <bitset>
#include <memory.h>
#include <vector>
#include <stack>
#include <set>

using namespace std;
const int MAXN = 1005;

bitset<MAXN> graph[MAXN] ,articular ,visit ,bcc_check[MAXN];
vector<int> G[MAXN] ,bcc[MAXN];
int low[MAXN] ,dfn[MAXN] ,dft ,nbcc;
stack<int> stk;
bitset<MAXN> color ,odd;

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
                for(int x = 0;x != V;stk.pop()) x = stk.top() ,bcc[nbcc].push_back(x) ,bcc_check[nbcc][x] = true;
                bcc[nbcc].push_back(on) ,bcc_check[nbcc++][on] = true;
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
    if(!bcc_check[code][on]) return false;
    if(visit[on]) return color[on] != col;
    visit[on] = true;
    color[on] = col;
    for(int V : G[on]) if(draw(V ,code ,!col)) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,M ,src ,dst ,ans;
    int i ,j;
    while(cin >> N >> M ,!(N == 0 && M == 0)) {
        for(i = 0;i < MAXN;i++) {
            G[i] = vector<int>();
            graph[i].reset();
            bcc[i] = vector<int>();
            bcc_check[i].reset();
        }
        nbcc = ans = dft = 0;
        memset(low ,0 ,sizeof(low)), memset(dfn ,0 ,sizeof(dfn));
        articular.reset(), visit.reset();
        while(M--) {
            cin >> src >> dst;
            graph[src][dst] = graph[dst][src] = true;
        }
        for(i = 1;i <= N;i++) for(j = 1;j <= N;j++) if(!graph[i][j] && i != j) G[i].push_back(j);
        for(i = 1;i <= N;i++) if(!visit[i]) dfs(i ,-1);
        odd.reset();
        for(i = 0;i < nbcc;i++) {
            visit.reset(), color.reset();
            bool result = draw(bcc[i][0] ,i ,true);
            /*for(int item : bcc[i]) cout << item << " ";
            cout << (result ? "T" : "F") << endl;*/
            for(int item : bcc[i]) odd[item] = odd[item] || result;
        }
        for(i = 1;i <= N;i++) if(!odd[i]) ans += 1;
        cout << ans << endl;
    }
}
/*
5 5
1 4
1 5
2 5
3 4
4 5
0 0
*/
