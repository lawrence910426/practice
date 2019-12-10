///#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;
const int MAXN = 5e5 + 50;
vector<int> G[MAXN];
int low[MAXN] ,dfn[MAXN] ,dft ,nbcc;
int N ,M;
bitset<MAXN> visit;
set<int> cut ,bcc[MAXN];
stack<int> stk;

void tarjan(int on ,int parent) {
    visit[on] = true;
    low[on] = dfn[on] = dft++;
    stk.push(on);
    int son = 0;
    for(int V : G[on]) {
        if(visit[V]) {
            if(V != parent) low[on] = min(dfn[V] ,low[on]);
        } else {
            son += 1;
            tarjan(V ,on);
            low[on] = min(low[V] ,low[on]);
            if(low[V] >= dfn[on]) {
                if(parent != -1) cut.insert(on);
                for(int x = 0;x != V;stk.pop()) {
                    x = stk.top();
                    bcc[x].insert(nbcc);
                }
                bcc[on].insert(nbcc++);
            }
        }
    }
    if(parent == -1 && son > 1) cut.insert(on);
}

int main() {
    //ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,src ,dst;
    bool no;
    while(cin >> N >> M) {
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        while(M--) {
            cin >> src >> dst;
            G[src].push_back(dst);
            G[dst].push_back(src);
        }
        visit.reset() ,nbcc = dft = 0 ,cut = set<int>() ,stk = stack<int>();
        for(i = 0;i < MAXN;i++) bcc[i] = set<int>();
        for(i = 1;i <= N;i++) if(!visit[i]) tarjan(i ,-1);
        no = true;
        for(int V : cut) {
            no = false;
            cout << V << ": ";
            for(int U : bcc[V]) cout << U << " ";
        }
        if(no) cout << "None";
        cout << '\n';
    }
}
