#pragma GCC optimize("Ofast")

#include <iostream>
#include <bitset>
#include <vector>
#include <queue>
#include <memory.h>
#include <set>

using namespace std;
const int MAXV = 2e6 + 50 ,MAXE = 1e7 + 50 ,INF = (1LL << 31) - 1 ,dx[2] = {0 ,1} ,dy[2] = {1 ,0};
class Dinic {
    int src ,dst ,used ,ptr[MAXV] ,depth[MAXV];
    struct E { int src ,dst, cap ,flow; } edges[MAXE];
    bitset<MAXV> visit; vector<int> G[MAXV];
    int Dfs(int on ,int cap) {
        int flow = 0 ,temp;
        if(cap == 0 || on == dst) return cap;
        for(int& i = ptr[on];i < G[on].size();i++) {
            int code = G[on][i];
            E edg = edges[code];
            if(depth[edg.src] + 1 == depth[edg.dst]) {
                temp = Dfs(edg.dst ,min(cap ,edg.cap - edg.flow));
                if(temp > 0) {
                    cap -= temp; flow += temp;
                    edges[code].flow += temp; edges[code ^ 1].flow -= temp;
                    if(cap == 0) break;
                }
            }
        }
        return flow;
    }
    bool Bfs() {
        visit.reset(); visit[src] = true; depth[src] = 0;
        queue<int> Q;
        for(Q.push(src);!Q.empty();Q.pop()) {
            for(int i : G[Q.front()]) {
                E edg = edges[i];
                if(!visit[edg.dst] && edg.cap > edg.flow) {
                    visit[edg.dst] = true; Q.push(edg.dst);
                    depth[edg.dst] = depth[edg.src] + 1;
                }
            }
        }
        return visit[dst];
    }
public:
    Dinic() {
        memset(edges ,0 ,sizeof(edges)); used = 0;
        for(int i = 0;i < MAXV;i++) G[i] = vector<int>();
    }
    void Add_Edge(int src ,int dst ,int cap) {
        edges[used++] = E{src ,dst ,cap ,0}; edges[used++] = E{dst ,src ,0 ,0};
        G[src].push_back(used - 2); G[dst].push_back(used - 1);
    }
    int Max_Flow(int src ,int dst) {
        this->src = src; this->dst = dst;
        int ans = 0;
        while(Bfs()) {
            memset(ptr ,0 ,sizeof(ptr));
            ans += Dfs(src ,INF);
        }
        return ans;
    }
} Flow;

set<pair<int ,int> > Block;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,M;
    int i ,j ,k ,x ,y;
    char temp;
    cin >> N >> M;
    for(i = 0;i < N;i++) for(j = 0;j < M;j++) {
        cin >> temp;
        if(temp == '#') Block.insert({i ,j});
    }
    for(i = 0;i < N;i++) for(j = 0;j < M;j++) Flow.Add_Edge((i * M + j) + 0 ,(i * M + j) + N * M ,1);
    for(i = 0;i < N;i++) for(j = 0;j < M;j++) for(k = 0;k < 2;k++) {
        x = i + dx[k]; y = j + dy[k];
        if(Block.find({x ,y}) != Block.end()) continue;
        if(x >= N || y >= M || x < 0 || y < 0) continue;
        Flow.Add_Edge((i * M + j) + N * M ,(x * M + y) + 0 ,INF);
    }
    cout << Flow.Max_Flow(N * M ,N * M - 1) << endl;
}
/*
4 5
.....
....#
.....
..#..
*/
