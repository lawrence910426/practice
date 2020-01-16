#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <bitset>
#include <memory.h>
#include <set>

using namespace std;
const int MAXN = 1e4 + 50;
int N ,M;
vector<int> G[MAXN];
int dfn[MAXN] ,low[MAXN] ,dft;
bitset<MAXN> visit ,is_cut;
set<int> articular;

void tarjan(int on ,int parent) {
    visit[on] = true;
    low[on] = dfn[on] = dft++;
    int son = 0;
    for(int V : G[on]) {
        if(!visit[V]) {
            son += 1;
            tarjan(V ,on);
            low[on] = min(low[on] ,low[V]);
            if(low[V] >= dfn[on]) if(parent != -1) {
                is_cut[on] = true;
                articular.insert(on);
            }
        } else if(V != parent) {
            low[on] = min(low[on] ,dfn[V]);
        }
    }
    if(parent == -1 && son >= 2) {
        is_cut[on] = true;
        articular.insert(on);
    }
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,src ,dst ,counter = 0;
    vector<int> ans;
    while(cin >> N >> M ,!(N == 0 && M == 0)) {
        dft = 0;
        memset(dfn ,0 ,sizeof(dfn));
        memset(low ,0 ,sizeof(low));
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        for(i = 0;i < M;i++) {
            cin >> src >> dst;
            G[src].push_back(dst);
            G[dst].push_back(src);
        }
        is_cut.reset() ,visit.reset();
        for(i = 1;i <= N;i++) if(!visit[i]) tarjan(i ,-1);

        /*ans = vector<int>();
        for(i = 1;i <= N;i++) if(is_cut[i]) ans.push_back(i);*/

        cout << "Case #" << ++counter << ":" << articular.size() << " ";
        if(articular.size() == 0) cout << 0;
        else for(int item : articular) cout << item << " ";
        cout << '\n';
    }
}
