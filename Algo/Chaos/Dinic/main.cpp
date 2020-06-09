#pragma GCC optimize("Ofast")

#include <iostream>
#include <bitset>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;
const int MAXV = 1e3 + 50 ,MAXE = 1e3 + 50;
const long long INF = (1LL << 63) - 1;
class Dinic {
    int src ,dst ,used;
    int ptr[MAXV] ,depth[MAXV];
    struct E {
        int src ,dst; long long cap ,flow;
        E() {}
        E(int s ,int d ,long long c ,long long f): src(s) ,dst(d) ,cap(c) ,flow(f) {}
    } edges[MAXE];
    vector<int> G[MAXV];
    bitset<MAXV> visit;
    bool Bfs() {
        visit.reset(); visit[src] = true; depth[src] = 0;
        queue<int> Q;
        for(Q.push(src);!Q.empty();Q.pop()) {
            for(int i = 0;i < G[Q.front()].size();i++) {
                E edg = edges[G[Q.front()][i]];
                if(!visit[edg.dst] && edg.cap > edg.flow) {
                    depth[edg.dst] = depth[edg.src] + 1;
                    visit[edg.dst] = true;
                    Q.push(edg.dst);
                }
            }
        }
        return visit[dst];
    }
    long long Dfs(int on ,long long cap) {
        if(on == dst || cap == 0) return cap;
        long long flow = 0 ,temp;
        for(int& i = ptr[on];i < G[on].size();i++) {
            int code = G[on][i];
            E edg = edges[code];
            if(depth[on] + 1 == depth[edg.dst]) {
                temp = Dfs(edg.dst ,min(cap ,edg.cap - edg.flow));
                if(temp > 0) {
                    edges[code].flow += temp;
                    edges[code ^ 1].flow -= temp;
                    cap -= temp;
                    flow += temp;
                    if(cap == 0) break;
                }
            }
        }
        return flow;
    }
public:
    Dinic() {
        memset(edges ,0 ,sizeof(edges)); used = 0;
        for(int i = 0;i < MAXV;i++) G[i] = vector<int>();
    }
    void Add_Edge(int src ,int dst ,long long cap) {
        edges[used++] = E(src ,dst ,cap ,0); edges[used++] = E(dst ,src ,0 ,0);
        G[src].push_back(used - 2); G[dst].push_back(used - 1);
    }
    long long Max_Flow(int s ,int t) {
        long long flow_sum = 0;
        this->src = s; this->dst = t;
        while(Bfs()) {
            memset(ptr ,0 ,sizeof(ptr));
            flow_sum += Dfs(s ,INF);
        }
        return flow_sum;
    }
} MaxFlow;

int main() {
    int N ,M;
    int src ,dst ,cap;
    int i;
    ios::sync_with_stdio(0) ,cin.tie(0);
    while(cin >> N >> M) {
        MaxFlow = Dinic();
        for(i = 0;i < N;i++) {
            cin >> src >> dst >> cap;
            MaxFlow.Add_Edge(src ,dst ,cap);
        }
        cout << MaxFlow.Max_Flow(1 ,M) << endl;
    }
}
