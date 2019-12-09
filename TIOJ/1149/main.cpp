#include <iostream>
#include <stack>
#include <vector>
#include <bitset>
#include <memory.h>

using namespace std;
const int MAXN = 1e4 + 10;
vector<int> G[MAXN];
int low[MAXN] ,dfn[MAXN] ,dft ,nscc;
stack<int> stk;
bitset<MAXN> in_stack ,visit ,scc[MAXN];

void tarjan(int on) {
    visit[on] = true;
    dfn[on] = low[on] = dft++;
    in_stack[on] = true ,stk.push(on);
    for(int V : G[on]) {
        if(!visit[V]) {
            tarjan(V);
            low[on] = min(low[on] ,low[V]);
        } else if(dfn[on] > dfn[V] && in_stack[V]) {
            low[on] = min(low[on] ,dfn[V]);
        }
    }
    if(dfn[on] == low[on]) {
        for(int x = -1;x != on;stk.pop()) {
            x = stk.top();
            in_stack[x] = false;
            scc[nscc][x] = true;
        }
        nscc += 1;
    }
}

int get_code(string s) {
    if(s.size() == 2) return s[1] - '1';
    else return (s[1] - '0') * 10 + s[2] - '1';
}

int main() {
    int T ,N ,M ,ca ,cb;
    string a ,b;
    int i ,j;
    bool compatible;
    while(cin >> T) {
        while(T--) {
            for(i = 0;i < MAXN;i++) G[i] = vector<int>() ,scc[i].reset();
            memset(low ,0 ,sizeof(low)) ,memset(dfn ,0 ,sizeof(dfn));
            dft = nscc = 0;
            stk = stack<int>();
            in_stack.reset() ,visit.reset();
            compatible = true;
            cin >> N >> M;
            while(M--) {
                cin >> a >> b;
                ca = get_code(a) ,cb = get_code(b);
                if(a[0] == 'm' && b[0] == 'm') { /* a || b */
                    G[ca + N].push_back(cb);
                    G[cb + N].push_back(ca);
                } else if(a[0] == 'h' && b[0] == 'm') { /* !a || b */
                    G[ca].push_back(cb);
                    G[cb + N].push_back(ca + N);
                } else if(a[0] == 'm' && b[0] == 'h') { /* a || !b */
                    G[ca + N].push_back(cb + N);
                    G[cb].push_back(ca);
                } else if(a[0] == 'h' && b[0] == 'h') { /* !a || !b */
                    G[ca].push_back(cb + N);
                    G[cb].push_back(ca + N);
                }
            }
            for(i = 0;i < N * 2;i++) {
                visit.reset();
                in_stack.reset();
                tarjan(i);
            }
            /*cout << "Graph:" << endl;
            for(i = 0;i < N * 2;i++) for(int V : G[i]) cout << i << " " << V << endl;
            cout << "SCC:" << endl;
            for(i = 0;i < nscc;cout << endl ,i++) for(int V = 0;V < N * 2;V++) if(scc[i][V]) cout << V << " ";*/
            for(i = 0;i < nscc;i++) for(j = 0;j < N;j++) compatible &= !(scc[i][j] && scc[i][j + N]);
            cout << (compatible ? "GOOD" : "BAD") << endl;
        }
    }
}
