#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;
const int MAXV = 5005, MAXE = 5000, INF = (1LL << 31) - 1, SRC = 5001, DST = 5002;

class Dinic {
    int ptr[MAXV] ,used = 0, depth[MAXV], src, dst;
    vector<int> G[MAXV]; bitset<MAXV> visit;
    bool bfs() {
        memset(depth, -1, sizeof(depth)); visit.reset();
        queue<int> Q; visit[src] = true; depth[src] = 0;
        for(Q.push(src);!Q.empty();Q.pop()) {
            for(int e : G[Q.front()]) {
                E edg = Edge[e];
                if(edg.cap > edg.flow && !visit[edg.dst]) {
                    depth[edg.dst] = depth[edg.src] + 1;
                    visit[edg.dst] = true;
                    Q.push(edg.dst);
                }
            }
        }
        return visit[dst];
    }
    int dfs(int on, int flow) {
        if(on == dst) return flow;
        int ans = 0;
        for(int& i = ptr[on];i < G[on].size();i++) {
            E edg = Edge[G[on][i]];
            if(depth[edg.src] == depth[edg.dst] + 1 && flow > 0) {
                int temp = dfs(edg.dst, min(flow, edg.cap - edg.flow));
                flow -= temp;
                Edge[G[on][i]].flow += temp;
                Edge[G[on][i] ^ 1].flow -= temp;
                ans += temp;
                if(flow == 0) break;
            }
        }
        return ans;
    }
public:
    struct E { int src, dst, cap, flow; } Edge[MAXE];
    Dinic() {
        memset(Edge, 0, sizeof(Edge)); used = 0;
        for(int i = 0;i < MAXV;i++) G[i] = vector<int>();
    }
    void AddEdge(int src, int dst, int cap) {
        Edge[used++] = { src, dst, cap ,0 };
        Edge[used++] = { dst, src, 0, 0 };
        G[src].push_back(used - 2); G[dst].push_back(used - 1);
    }
    int MaxFlow(int src, int dst) {
        int ans = 0;
        this->src = src; this->dst = dst;
        while(bfs()) {
            memset(ptr, 0, sizeof(ptr));
            ans += dfs(src, INF);
        }
        return ans;
    }
} Flow;

int main() {
    int T, N, M, A, B, MaxFlow; int i, j;
    for(cin >> T;T--;) {
        Flow = Dinic();
        cin >> N >> M >> A >> B;
        for(i = 0;i < N;i++) Flow.AddEdge(SRC, i * M, A);
        for(i = 0;i < N;i++) for(j = 0;j < M - 1;j++) Flow.AddEdge(i * M + j, i * M + j + 1, INF);
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) Flow.AddEdge(i * M + j, N * M + j, INF);
        for(j = 0;j < M;j++) Flow.AddEdge(N * M + j, DST, B);
        MaxFlow = Flow.MaxFlow(SRC, DST);
        cout << (MaxFlow == M * B && MaxFlow == N * A ? "YES" : "NO") << endl;
    }
}
