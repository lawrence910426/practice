#include <iostream>
#include <vector>
#include <bitset>
#pragma GCC optimize("Ofast,no-stack-protector")
using namespace std;
const int MAXV = 300;
struct e {
    int src ,dst ,cap ,rev;
    e(int s ,int d ,int c ,int r): src(s) ,dst(d) ,cap(c) ,rev(r) {}
};
int E ,V;
vector<e> G[MAXV];
bitset<MAXV> visit;

int dfs(int on ,int dst ,int cap) {
    if(on == dst) return cap;
    visit[on] = true;
    for(int i = 0;i < G[on].size();i++) {
        e edge = G[on][i];
        if(visit[edge.dst] || edge.cap <= 0) continue;
        int congest = dfs(edge.dst ,dst ,min(cap ,edge.cap));
        if(congest > 0) {
            G[on][i].cap -= congest;
            G[edge.dst][edge.rev].cap += congest;
            return congest;
        }
    }
    return 0;
}

int MaxFlow(int s ,int t) {
    int answer = 0 ,path_flow;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(true) {
        visit.reset();
        path_flow = dfs(s ,t ,(1LL << 31) - 1);
        if(path_flow == 0) return answer;
        answer += path_flow;
    }
}

int main() {
    int src ,dst ,val;
    while(cin >> E >> V) {
        while(E--) {
            cin >> src >> dst >> val;
            G[src].push_back(e(src ,dst ,val ,G[dst].size()));
            G[dst].push_back(e(dst ,src ,0 ,G[src].size() - 1));
        }
        cout << MaxFlow(1 ,V) << endl;
    }
}
