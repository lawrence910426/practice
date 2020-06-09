#include <iostream>
#include <bitset>
#include <queue>

using namespace std;
const int MAXN = 300;
int rG[MAXN][MAXN] ,s ,t ,parent[MAXN] ,E ,V;
bitset<MAXN> visit;

bool bfs() {
    visit.reset();
    queue<int> Q = queue<int>();
    visit[s] = true;
    parent[s] = -1;
    for(Q.push(s);!Q.empty();Q.pop()) {
        int on = Q.front();
        for(int to = 1;to <= V;to++) {
            if(visit[to] || rG[on][to] <= 0) continue;
            parent[to] = on;
            visit[to] = true;
            Q.push(to);
        }
    }
    return visit[t];
}

int MinCostMaxFlow() {
    int max_flow = 0 ,path_flow ,i;
    while(bfs()) {
        path_flow = (1LL << 31) - 1;
        for(i = t;i != s;i = parent[i])
            path_flow = min(path_flow ,rG[parent[i]][i]);
        for(i = t;i != s;i = parent[i]) {
            rG[parent[i]][i] -= path_flow;
            rG[i][parent[i]] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    int i ,eax ,ebx ,ecx;
    while(cin >> E >> V) {
        s = 1, t = V;
        memset(rG ,0 ,sizeof(rG));
        while(E--) {
            cin >> eax >> ebx >> ecx;
            rG[eax][ebx] = ecx;
        }
        cout << MinCostMaxFlow() << endl;
    }
}
