#include <iostream>
#include <queue>
#include <memory.h>
#include <vector>
#include <bitset>

using namespace std;
const int MAXV = 1e5 ,MAXE = 1e5 ,INF = (1LL << 31) - 1;
class Dinic {
    struct E { int src ,dst; long long cap ,flow; } Edge[MAXE];
    vector<int> G[MAXV]; bitset<MAXV> visit;
    int used ,src ,dst ,iter[MAXV] ,depth[MAXV];
    bool Bfs() {
        visit.reset(); visit[src] = true; depth[src] = 0; queue<int> Q;
        for(Q.push(src);!Q.empty();Q.pop()) for(int i : G[Q.front()]) {
            E edg = Edge[i];
            if(edg.flow < edg.cap && !visit[edg.dst]) {
                depth[edg.dst] = depth[edg.src] + 1;
                Q.push(edg.dst); visit[edg.dst] = true;
            }
        }
        return visit[dst];
    }
    long long Dfs(int on ,long long cap) {
        if(on == dst) return cap;
        long long ans = 0 ,flow;
        for(int& i = iter[on];i < G[on].size();i++) {
            int ptr = G[on][i]; E edg = Edge[ptr];
            if(edg.flow < edg.cap && depth[edg.src] + 1 == depth[edg.dst]) {
                flow = Dfs(edg.dst ,min(cap ,edg.cap - edg.flow));
                Edge[ptr].flow += flow; Edge[ptr ^ 1].flow -= flow;
                cap -= flow; ans += flow;
                if(cap == 0) break;
            }
        }
        return ans;
    }
public:
    void Add_Edge(int src ,int dst ,long long cap) {
        Edge[used++] = E{src ,dst ,cap ,0};
        Edge[used++] = E{dst ,src ,0 ,0};
        G[src].push_back(used - 2); G[dst].push_back(used - 1);
    }
    long long Flow(int src ,int dst) {
        this->src = src; this->dst = dst;
        long long ans = 0;
        while(Bfs()) {
            memset(iter ,0 ,sizeof(iter));
            ans += Dfs(src ,INF);
        }
        return ans;
    }
    Dinic() {
        memset(Edge ,-1 ,sizeof(Edge)); used = 0;
        for(int i = 0;i < MAXV;i++) G[i] = vector<int>();
    }
} MaxFlow;

int N ,S ,T ,edges ,src ,dst ,cap ,counter = 0;
int main() {
    while(cin >> N ,N) {
        cin >> S >> T >> edges; MaxFlow = Dinic();
        while(edges--) {
            cin >> src >> dst >> cap;
            MaxFlow.Add_Edge(src ,dst ,cap);
            MaxFlow.Add_Edge(dst ,src ,cap);
        }
        printf("Network %d\n" ,++counter);
        printf("The bandwidth is %d.\n\n" ,MaxFlow.Flow(S ,T));
    }
}
