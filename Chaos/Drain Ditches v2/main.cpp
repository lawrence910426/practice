#include <iostream>
#include <memory.h>
#include <vector>
#include <bitset>

using namespace std;
const int MAXV = 300;
int V;
struct edge {
    int src, dst ,cap ,rev;
    edge(int s ,int d ,int c ,int r): src(s) ,dst(d) ,cap(c) ,rev(r) {}
};
vector<edge> G[MAXV];
bitset<MAXV> visit;
int dfs(int on ,int dst ,int cap) {
    if(on == dst) return cap;
    visit[on] = true;
    for(int i = 0;i < G[on].size();i++) {
        edge &e = G[on][i];
        if(visit[e.dst] || e.cap <= 0) continue;
        int congest = dfs(e.dst ,dst ,min(cap ,e.cap));
        if(congest > 0) {
            e.cap -= congest;
            G[e.dst][e.rev].cap += congest;
            return congest;
        }
    }
    return 0;
}

int MaxFlow(int src ,int dst) {
    int path_flow ,max_flow = 0;
    while(true) {
        visit.reset();
        path_flow = dfs(src ,dst ,(1LL << 31) - 1);
        if(path_flow == 0) return max_flow;
        max_flow += path_flow;
    }
}

int main() {
    int E ,src, dst, weight;
    int i;
    while(cin >> E >> V) {
        for(i = 0;i < MAXV;i++) G[i] = vector<edge>();
        while(E--) {
            cin >> src >> dst >> weight;
            G[src].push_back(edge(src ,dst ,weight ,G[dst].size()));
            G[dst].push_back(edge(dst ,src ,0 ,G[src].size() - 1));
        }
        cout << MaxFlow(1 ,V) << endl;
    }
}
