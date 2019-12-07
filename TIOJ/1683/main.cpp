#include <iostream>
#include <vector>
#include <bitset>
#include <stack>
#include <memory.h>

using namespace std;
const int MAXN = 10005;
int low[MAXN] ,dfn[MAXN] ,dft ,nscc ,weight[MAXN] ,dsu[MAXN];
vector<int> G[MAXN] ,scc[MAXN] ,G2[MAXN];
bitset<MAXN> visit ,in_stack ,is_entry;
stack<int> stk;

int boss(int x) { return (x == dsu[x] ? x : dsu[x] = boss(dsu[x])); }
void join(int a ,int b) {
    a = boss(a) ,b = boss(b);
    if(a == b) return;
    weight[b] += weight[a];
    weight[a] = 0;
    dsu[a] = dsu[b];
}

void tarjan(int on) {
    visit[on] = true;
    dfn[on] = low[on] = dft++;
    stk.push(on) ,in_stack[on] = true;
    for(int V : G[on]) {
        if(!visit[V]) {
            tarjan(V);
            low[on] = min(low[on] ,low[V]);
        } else if(dfn[V] < dfn[on] && in_stack[V]) {
            low[on] = min(low[on] ,dfn[V]);
        }
    }
    if(dfn[on] == low[on]) {
        for(int x = 0;x != on;stk.pop()) {
            x = stk.top();
            in_stack[x] = false;
            scc[nscc].push_back(x);
        }
        nscc += 1;
    }
}

int longest_route(int on) {
    int ans = 0;
    for(int V : G2[on]) ans = max(ans ,longest_route(V));
    return ans + weight[on];
}

int main() {
    int T ,N ,M ,ans;
    int src ,dst ,i ,tmp_a ,tmp_b;
    for(cin >> T;T--;) {
        cin >> N >> M;
        for(i = 0;i < MAXN;i++) {
            G[i] = vector<int>();
            G2[i] = vector<int>();
            scc[i] = vector<int>();
            dsu[i] = i;
            weight[i] = 1;
        }
        memset(low ,0 ,sizeof(low)) ,memset(dfn ,0 ,sizeof(dfn));
        dft = nscc = ans = 0;
        stk = stack<int>();
        visit.reset() ,in_stack.reset();
        is_entry.reset() ,is_entry.flip();

        while(M--) {
            cin >> src >> dst;
            G[src].push_back(dst);
        }
        for(i = 1;i <= N;i++) if(!visit[i]) tarjan(i);
        for(i = 0;i < nscc;i++) for(int V : scc[i]) join(V ,scc[i][0]);
        for(i = 1;i <= N;i++) for(int V : G[i]) {
            tmp_a = boss(V) ,tmp_b = boss(i);
            if(tmp_a == tmp_b) continue;
            G2[tmp_b].push_back(tmp_a);
            is_entry[tmp_a] = false;
        }
        /*for(i = 1;i <= N;cout << endl ,i++) for(int V : G2[i]) cout << V << " ";*/
        for(i = 0;i < nscc;i++) {
            tmp_a = boss(scc[i][0]);
            if(is_entry[tmp_a]) ans = max(ans ,longest_route(tmp_a));
        }
        cout << ans << endl;
    }
}
