#include <iostream>
#include <queue>
#include <bitset>
#include <memory.h>
#include <ostream>

using namespace std;
const int MAXV = 1e5 + 50 ,MAXE = 2e5 + 50 ,INF = (1LL << 31) - 1;

class Dinic {
    struct E { int src ,dst; long long cap ,flow; } Edge[MAXE];
    vector<int> G[MAXV]; bitset<MAXV> visit;
    int used ,src ,dst ,depth[MAXV] ,iter[MAXV];
    bool Bfs() {
        queue<int> Q; visit.reset(); depth[src] = 0; visit[src] = true;
        for(Q.push(src);!Q.empty();Q.pop()) for(int i : G[Q.front()]) {
            E edg = Edge[i];
            if(edg.flow < edg.cap && !visit[edg.dst]) {
                depth[edg.dst] = depth[edg.src] + 1;
                visit[edg.dst] = true;
                Q.push(edg.dst);
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
                ans += flow; cap -= flow;
                if(cap == 0) break;
            }
        }
        return ans;
    }
public:
    Dinic() {
        memset(Edge ,-1 ,sizeof(Edge)); used = 0;
        for(int i = 0;i < MAXV;i++) G[i] = vector<int>();
    }
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
} MaxFlow;

int N ,S ,T ,src ,dst ,edges ,cap ,counter;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("output.txt" ,"w" ,stdout);
    while(cin >> N ,N) {
        cin >> S >> T >> edges; MaxFlow = Dinic();
        while(edges--) {
            cin >> src >> dst >> cap;
            MaxFlow.Add_Edge(src ,dst ,cap);
            MaxFlow.Add_Edge(dst ,src ,cap);
        }
        cout << "Network " << ++counter << "\n";
        cout << "The bandwidth is " << MaxFlow.Flow(S ,T) << ".\n\n";
    }
}
