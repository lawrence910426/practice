#include <iostream>
#include <bitset>
#include <vector>
#include <memory.h>
#include <queue>

using namespace std;
const int MAXN = 300 ,src = 251 ,dst = 252 ,INF = (1LL << 31) - 1;
using namespace std;
struct edge {
    int src ,dst;
    long long int flow ,cap ,cost;
    edge() {}
    edge(int s ,int d ,long long f ,long long ca ,long long co):
        src(s) ,dst(d) ,flow(f) ,cap(ca) ,cost(co) {}
};
bitset<MAXN> visit;
long long int cap[MAXN] ,dis[MAXN];
long long int maxFlow ,minCost;
int pre[MAXN];
vector<int> G[MAXN];
vector<edge> edges;

inline void init() {
    edges = vector<edge>();
    for(int i = 0;i < MAXN;i++) G[i] = vector<int>();
    visit.reset();
    maxFlow = minCost = 0;
}

inline void add_edge(int src ,int dst ,long long int cap ,long long int cost) {
    edge e1 = edge(src ,dst ,0 ,cap ,cost);
    edge e2 = edge(dst ,src ,0 ,0 ,-cost);
    edges.push_back(e1);
    edges.push_back(e2);
    G[src].push_back(edges.size() - 2);
    G[dst].push_back(edges.size() - 1);
}

inline bool bellman_ford() {
    int i;
    edge e;
    for(i = 0;i < MAXN;i++) dis[i] = INF;
    visit.reset();
    memset(pre ,-1 ,sizeof(pre));
    memset(cap ,0 ,sizeof(cap));
    cap[src] = INF;
    dis[src] = 0;
    queue<int> Q = queue<int>();
    visit[src] = true;
    for(Q.push(src);!Q.empty();Q.pop()) {
        int U = Q.front();
        visit[U] = false;
        for(i = 0;i < G[U].size();i++) {
            e = edges[G[U][i]];
            if(e.cap > e.flow && dis[e.dst] > dis[U] + e.cost) {
                dis[e.dst] = dis[U] + e.cost;
                pre[e.dst] = G[U][i];
                cap[e.dst] = min(cap[e.src] ,e.cap - e.flow);
                if(!visit[e.dst]) {
                    Q.push(e.dst);
                    visit[e.dst] = true;
                }
            }
        }
    }
    if(dis[dst] == INF) return false;
    maxFlow += cap[dst];
    minCost += cap[dst] * dis[dst];
    for(i = dst;i != src;i = edges[pre[i]].src) {
        edges[pre[i]].flow += cap[dst];
        edges[pre[i] ^ 1].flow -= cap[dst];
    }
    return true;
}

inline void MinCostMaxFlow() { while(bellman_ford()) ; }

int main() {
    int T ,N ,M;
    int i ,j ,eax;
    for(cin >> T;T--;) {
        init();
        cin >> N >> M;
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) {
            cin >> eax;
            if(eax != 0) add_edge(i ,j + 100 ,1 ,eax);
        }
        for(i = 0;i < N;i++) add_edge(src ,i ,1 ,0);
        for(i = 0;i < M;i++) {
            cin >> eax;
            add_edge(i + 100 ,dst ,eax ,0);
        }
        MinCostMaxFlow();
        cout << (maxFlow == N ? minCost : -1) << endl;
    }
}
