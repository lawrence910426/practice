#include <iostream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;
const int MAXN = 300 ,INF = (1LL << 31) - 1 ,source = 251 ,dest = 252;
struct edge {
    int src ,dst ,cap ,cost ,rev;
    edge() {}
    edge(int s ,int d ,int cp ,int co ,int r): src(s) ,dst(d) ,cap(cp) ,cost(co) ,rev(r) {}
};
vector<edge> G[MAXN];
int dis[MAXN] ,pre[MAXN][2];
bitset<MAXN> visit;

bool spfa() {
    int i ,U;
    edge E;
    for(i = 0;i <= MAXN;i++) dis[i] = INF;
    visit.reset();
    dis[source] = 0;

    queue<int> Q;
    Q.push(source);
    visit[source] = true;
    for(;!Q.empty();Q.pop()) {
        U = Q.front();
        for(i = 0;i < G[U].size();i++) {
            E = G[U][i];
            int V = E.dst;
            if(E.cap > 0 && dis[V] > dis[U] + E.cost) {
                dis[V] = dis[U] + E.cost;
                pre[V][0] = U;
                pre[V][1] = i;
                if(!visit[V]) {
                    visit[V] = true;
                    Q.push(V);
                }
            }
        }
        visit[U] = false;
    }
    return dis[dest] != INF;
}

void MinCostMaxFlow(int& cost ,int& flow) {
    int path_flow ,path_cost ,V;
    while(spfa()) {
        path_flow = INF;
        path_cost = 0;
        for(V = dest;V != source;V = G[pre[V][0]][pre[V][1]].src) path_flow = min(path_flow ,G[pre[V][0]][pre[V][1]].cap);
        for(V = dest;V != source;V = G[pre[V][0]][pre[V][1]].src) {
            edge e = G[pre[V][0]][pre[V][1]];
            G[pre[V][0]][pre[V][1]].cap -= path_flow;
            G[e.dst][e.rev].cap += path_flow;
            path_cost += path_flow * e.cost;
        }
        cost += path_cost;
        flow += path_flow;
    }
}

int main() {
    int T ,N ,M ,cost ,flow;
    int i ,j ,eax;
    for(cin >> T;T--;) {
        cin >> N >> M;
        for(i = 0;i < N;i++) G[i] = vector<edge>();
        for(i = 0;i < N;i++) for(j = 100;j < 100 + M;j++) {
            cin >> eax;
            if(eax == 0) continue;
            G[i].push_back(edge(i ,j ,1 ,eax    ,G[j].size()));
            G[j].push_back(edge(j ,i ,0 ,-eax   ,G[i].size() - 1));
        }
        for(i = 0;i < N;i++) {
            G[source].push_back(edge(source ,i      ,1      ,0 ,G[i].size()));
            G[i].push_back(     edge(i      ,source ,0      ,0 ,G[source].size() - 1));
        }
        for(i = 100;i < 100 + M;i++) {
            cin >> eax;
            G[i].push_back(     edge(i      ,dest   ,eax    ,0 ,G[dest].size()));
            G[dest].push_back(  edge(dest   ,0      ,0      ,0 ,G[i].size() - 1));
        }
        cost = flow = 0;
        MinCostMaxFlow(cost ,flow);
        cout << (flow == N ? cost : -1) << endl;
    }
}
