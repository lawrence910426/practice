#include <iostream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;
const int MAXN = 300 ,INF = (1LL << 31) - 1 ,src = 251 ,dst = 252;
struct edge {
    int src ,dst;
    long long cap ,flow ,cost;
    edge() {}
    edge(int s ,int d ,long long ca ,long long f ,long long co): src(s) ,dst(d) ,cap(ca) ,flow(f) ,cost(co) {}
};
vector<edge> edges;
vector<int> G[MAXN];
bitset<MAXN> visit;
long long cap[MAXN] ,dis[MAXN] ,min_cost ,max_flow;
int pre[MAXN];

inline void insert_edge(int src ,int dst ,int cap ,int cost) {
    edge e1 = edge(src ,dst ,cap ,0 ,cost) ,e2 = edge(dst ,src ,0 ,0 ,-cost);
    edges.push_back(e1) ,edges.push_back(e2);
    G[src].push_back(edges.size() - 2) ,G[dst].push_back(edges.size() - 1);
}

inline bool bellman_ford() {
    int i;
    edge e;
    for(i = 0;i < MAXN;i++) dis[i] = INF;
    queue<int> Q;
    dis[src] = 0 ,cap[src] = INF ,pre[src] = -1 ,visit[src] = true ,Q.push(src);
    while(!Q.empty()) {
        int U = Q.front();
        visit[U] = false ,Q.pop();
        for(i = 0;i < G[U].size();i++) {
            e = edges[G[U][i]];
            if(e.cap > e.flow && dis[e.dst] > dis[e.src] + e.cost) {
                dis[e.dst] = dis[e.src] + e.cost;
                pre[e.dst] = G[U][i];
                cap[e.dst] = min(cap[e.src] ,e.cap - e.flow);
                if(!visit[e.dst]) {
                    visit[e.dst] = true;
                    Q.push(e.dst);
                }
            }
        }
    }
    if(dis[dst] == INF) return false;
    max_flow += cap[dst];
    min_cost += dis[dst] * cap[dst];
    for(i = dst;i != src;i = edges[pre[i]].src) {
        edges[pre[i]].flow += cap[dst];
        edges[pre[i] ^ 1].flow -= cap[dst];
    }
    return true;
}

int main() {
    int T ,N ,M;
    int i ,j ,eax;
    for(cin >> T;T--;) {
        edges = vector<edge>();
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        min_cost = max_flow = 0;
        cin >> N >> M;
        for(i = 0;i < N;i++) insert_edge(src ,i ,1 ,0);
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) {
            cin >> eax;
            if(eax != 0) insert_edge(i ,100 + j ,1 ,eax);
        }
        for(i = 0;i < M;i++) {
            cin >> eax;
            insert_edge(100 + i ,dst ,eax ,0);
        }
        while(bellman_ford()) ;
        cout << (max_flow == N ? min_cost : -1) << endl;
    }
}
