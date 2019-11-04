#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
const int MAXV = 300;
struct edge {
    int src ,dst ,cap ,rev;
    edge(int s ,int d ,int c ,int r): src(s) ,dst(d) ,cap(c) ,rev(r) {}
};
vector<edge> G[300];
bitset<MAXV> visit;
int dfs(int on ,int dst ,int cap) {
    if(on == dst) return cap;
    visit[on] = true;
    for(int i = 0;i < G[on].size();i++) {
        edge e = G[on][i];
        if(visit[e.dst] || e.cap <= 0) continue;
        int congest = dfs(e.dst ,dst ,min(cap ,e.cap));
        if(congest > 0) {
            G[on][i].cap -= congest;
            G[e.dst][e.rev].cap += congest;
            return congest;
        }
    }
    return 0;
}

int MaxFlow(int s ,int t) {
    int max_flow = 0 ,path_flow;
    while(true) {
        visit.reset();
        path_flow = dfs(s ,t ,(1LL << 31) - 1);
        if(path_flow == 0) return max_flow;
        max_flow += path_flow;
    }
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int E, V ,src ,dst ,val;
    int i;
    while(cin >> E >> V) {
        for(i = 0;i < MAXV;i++) G[i] = vector<edge>();
        while(E--) {
            cin >> src >> dst >> val;
            G[src].push_back(edge(src ,dst ,val ,G[dst].size()));
            G[dst].push_back(edge(dst ,src ,0 ,G[src].size() - 1));
        }
        cout << MaxFlow(1 ,V) << '\n';
    }
}
