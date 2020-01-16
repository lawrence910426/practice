#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 5e3 + 50;
vector<pair<int ,int> > G[MAXN];
int N ,V ,Q;
int dfs(int on ,int parent ,int mini) {
    int ans = 0;
    if(parent != -1 && mini >= Q) ans += 1;
    for(auto p : G[on]) {
        if(p.first == parent) continue;
        ans += dfs(p.first ,on ,min(mini ,p.second));
    }
    return ans;
}
int main() {
    int i ,src, dst ,weight;
    while(cin >> N >> V >> Q) {
        for(i = 0;i < MAXN;i++) G[i] = vector<pair<int ,int> >();
        for(i = 0;i < N - 1;i++) {
            cin >> src >> dst >> weight;
            G[src].push_back(pair<int ,int>(dst ,weight));
            G[dst].push_back(pair<int ,int>(src ,weight));
        }
        cout << dfs(V ,-1 ,(1LL << 31) - 1) << endl;
    }
}
