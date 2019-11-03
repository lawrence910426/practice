#include <iostream>
#include <vector>
using namespace std;

vector<int> G[10005];
long long int weight[10005];

pair<long long int ,long long int> dfs(int parent ,int on ,int depth) {
    pair<long long int ,long long int> ans ,tmp;
    ans = pair<long long int ,long long int>(on ,depth * weight[on]);
    for(int V : G[on]) {
        if(V == parent) continue;
        tmp = dfs(on ,V ,depth + 1);
        if(tmp.second > ans.second) ans = tmp;
        if(tmp.second == ans.second) ans = (ans.first > tmp.first ? tmp : ans);
    }
    return ans;
}

int main() {
    int N ,M;
    int i ,eax ,ebx;
    while(cin >> N >> M) {
        for(i = 2;i <= N;i++) cin >> weight[i];
        for(i = 1;i <= N;i++) G[i] = vector<int>();
        for(i = 0;i < M;i++) {
            cin >> eax >> ebx;
            G[eax].push_back(ebx);
            G[ebx].push_back(eax);
        }
        auto ans = dfs(-1 ,1 ,0);
        cout << ans.first << " " << ans.second << endl;
    }
}
