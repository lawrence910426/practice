#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <bitset>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;
const int MAXN = 1000 + 5 ,MAXV = 3000 ,src = 2701 ,dst = 2702;
const long long INF = (1LL << 63) - 1;
struct edge {
    int src ,dst;
    long long cap ,flow ,cost;
    inline edge() {}
    inline edge(int s ,int d ,long long ca ,long long f ,long long co): src(s) ,dst(d) ,cap(ca) ,flow(f) ,cost(co) {}
}edges[MAXN * MAXN];
int used;
vector<int> G[MAXV];
inline void insert_edge(int src ,int dst ,long long cap ,long long cost) {
    edges[used++] = edge(src ,dst ,cap ,0 ,cost);
    edges[used++] = edge(dst ,src ,0 ,0 ,-cost);
    G[src].push_back(used - 2);
    G[dst].push_back(used - 1);
}

bitset<MAXV> visit;
long long dis[MAXV] ,flow[MAXV], min_cost ,max_flow;
int pre[MAXV];
inline bool bellman_ford() {
    int i ,U;
    edge e;
    visit.reset();
    for(i = 0;i < MAXV;i++) dis[i] = INF;
    queue<int> Q = queue<int>();
    dis[src] = 0 ,visit[src] = true ,flow[src] = INF ,pre[src] = -1;
    for(Q.push(src);!Q.empty();) {
        U = Q.front();
        Q.pop() ,visit[U] = false;
        for(i = 0;i < G[U].size();i++) {
            e = edges[G[U][i]];
            if(e.cap > e.flow && dis[e.dst] > dis[e.src] + e.cost) {
                dis[e.dst] = dis[e.src] + e.cost;
                pre[e.dst] = G[U][i];
                flow[e.dst] = min(flow[e.src] ,e.cap - e.flow);
                if(!visit[e.dst]) {
                    visit[e.dst] = true;
                    Q.push(e.dst);
                }
            }
        }
    }

    if(dis[dst] == INF) return false;
    max_flow += flow[dst];
    min_cost += dis[dst] * flow[dst];
    for(i = dst;i != src;i = edges[pre[i]].src) {
        edges[pre[i]].flow += flow[dst];
        edges[pre[i] ^ 1].flow -= flow[dst];
    }
    return true;
}

long long day[MAXN] ,night[MAXN];
bool abandon[MAXN][MAXN];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int T ,N ,K;
    int i ,j ,eax ,ebx;
    long long int L ,U;
    for(cin >> T;T--;) {
        memset(abandon ,0 ,sizeof(abandon));
        for(i = 0;i < MAXV;i++) G[i] = vector<int>();
        min_cost = max_flow = used = 0;

        cin >> N >> L >> U >> K;
        for(i = 0;i < K;i++) {
            cin >> eax >> ebx;
            eax -= 1 ,ebx -= 1;
            abandon[eax][ebx] = abandon[ebx][eax] = true;
        }
        for(i = 0;i < N;i++) cin >> day[i];
        for(i = 0;i < N;i++) cin >> night[i];
        for(i = 0;i < N;i++) insert_edge(src ,i ,1 ,0);
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) if(!abandon[i][j]) insert_edge(i ,MAXN + j ,1 ,min(max(0LL ,day[i] + night[j] - L) ,U - L));
        for(j = 0;j < N;j++) insert_edge(MAXN + j ,dst ,1 ,0);

        while(bellman_ford()) ;
        if(max_flow == N) cout << min_cost << '\n';
        else cout << "no" << '\n';
    }
}
