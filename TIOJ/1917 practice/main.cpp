#include <iostream>
#include <vector>
#include <memory.h>
#include <bitset>
#include <queue>
#include <stdio.h>

using namespace std;
const int MAXE = 1e6 + 50 ,MAXV = 3e3 ,SRC = 2500 ,DST = 2501 ,MAXN = 1200 ,INF = (1LL << 30) - 1;
int N ,L ,U ,K ,used;
struct edge {
    int src ,dst ,flow ,cap ,cost ;
    edge() {}
    edge(int S ,int D ,int F ,int CA ,int CO): src(S) ,dst(D) ,flow(F) ,cap(CA) ,cost(CO) {}
} E[MAXE];

vector<int> G[MAXV];
int dis[MAXV] ,pre[MAXV];
bool bellman_ford() {
    int i;
    for(i = 0;i < MAXV;i++) dis[i] = INF;
    for(i = 0;i < MAXV;i++) pre[i] = -1;
    queue<int> Q;
    bitset<MAXV> inqueue;
    inqueue[SRC] = true;
    dis[SRC] = 0;
    for(Q.push(SRC);!Q.empty();Q.pop()) {
        for(int code : G[Q.front()]) {
            edge e = E[code];
            if(e.flow < e.cap && dis[e.dst] > dis[e.src] + e.cost) {
                //printf("src:%d\tdst:%d\tcap:%d\tflow:%d\tcost:%d\tdis[src]:%d\tdis[dst]:%d\n" ,e.src ,e.dst ,e.cap ,e.flow ,e.cost ,dis[e.src] ,dis[e.dst]);
                dis[e.dst] = dis[e.src] + e.cost;
                pre[e.dst] = code;
                if(!inqueue[e.dst]) {
                    Q.push(e.dst);
                    inqueue[e.dst] = true;
                }
            }
        }
        inqueue[Q.front()] = false;
    }
    return dis[DST] != INF;
}
void MinCostMaxFlow(int& MaxFlow ,int& MinCost) {
    int flow ,cost ,ans_flow = 0 ,ans_cost = 0 ,pos;
    while(bellman_ford()) {
        flow = INF ,cost = 0;
        for(pos = DST;pre[pos] != -1;pos = E[pre[pos]].src) flow = min(flow ,E[pre[pos]].cap - E[pre[pos]].flow);
        for(pos = DST;pre[pos] != -1;pos = E[pre[pos]].src) {
            edge e = E[pre[pos]];
            //printf("src:%d\tdst:%d\tcap:%d\tflow:%d\tcost:%d\n" ,e.src ,e.dst ,e.cap ,e.flow ,e.cost);
            E[pre[pos]].flow += flow;
            E[pre[pos] ^ 1].flow -= flow;
            cost += E[pre[pos]].cost * flow;
        }
        //cout << flow << " " << cost << endl;
        //system("pause");
        ans_flow += flow;
        ans_cost += cost;
    }
    MaxFlow = ans_flow;
    MinCost = ans_cost;
}
void make_edge(int src, int dst ,int cap ,int cost) {
    E[used++] = edge(src ,dst ,0 ,cap ,cost);
    G[src].push_back(used - 1);
    E[used++] = edge(dst ,src ,cap ,cap ,-cost);
    G[dst].push_back(used - 1);
}

bool able[MAXV][MAXV];
int danger[MAXN][2];
int main() {
    int T ,i ,j ,src ,dst ,cost;
    int Flow ,Cost;
    for(cin >> T;T--;) {
        cin >> N >> L >> U >> K;
        memset(able ,-1 ,sizeof(able));
        used = 0;
        while(K--) {
            cin >> src >> dst;
            able[src][dst + MAXN] = false;
        }
        for(i = 1;i <= N;i++) cin >> danger[i][0];
        for(i = 1;i <= N;i++) cin >> danger[i][1];
        for(i = 1;i <= N;i++) for(j = 1;j <= N;j++) {
            src = i ,dst = j + MAXN;
            if(able[src][dst]) {
                cost = min(U - L ,max(0 ,danger[i][0] + danger[j][1] - L));
                make_edge(src ,dst ,1 ,cost);
            }
        }
        for(i = 1;i <= N;i++) make_edge(SRC ,i ,1 ,0);
        for(i = MAXN + 1;i <= MAXN + N;i++) make_edge(i ,DST ,1 ,0);
        MinCostMaxFlow(Flow ,Cost);
        //cout << Flow << " " << Cost << endl;
        if(Flow == N) cout << Cost << endl;
        else cout << "no" << endl;
    }
}
