#pragma GCC optimize("Ofast")
#include <iostream>
#include <map>
#include <vector>
using namespace std;
const int MAXN = 2e5 + 50;
map<int ,int> dp[MAXN];
vector<int> G[MAXN];
int val[MAXN];

void preprocess(int on ,int parent) {
    int ans = val[on];
    for(int i : G[on]) {
        if(i == parent) continue;
        preprocess(i ,on);
        ans += max(dp[i][on] ,0);
    }
    dp[on][parent] = ans;
}

void dfs(int on ,int parent) {
    if(parent != 0) dp[on][0] = dp[on][parent] + max(0 ,dp[parent][0] - max(0 ,dp[on][parent]));
    for(int i : G[on]) if(i != parent) dfs(i ,on);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int i ,src ,dst; int N; cin >> N;
    for(i = 1;i <= N;i++) { cin >> val[i]; val[i] = (val[i] == 1 ? 1 : -1); }
    for(i = 0;i < N - 1;i++) {
        cin >> src >> dst;
        G[src].push_back(dst);
        G[dst].push_back(src);
    }
    preprocess(1 ,0); dfs(1 ,0);
    for(i = 1;i <= N;i++) cout << dp[i][0] << " ";
}
