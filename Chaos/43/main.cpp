#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 3e2 + 5 ,MAXM = 5e4 + 5 ,INF = (1LL << 31) - 1;
struct edge { int src ,dst ,val; } data[MAXM];
bool cmp(edge a ,edge b) { return a.val < b.val; }
vector<int> G[MAXN];

int remove_min(int parent ,int on ,int target ,int mini) {
    if(on == target) return mini;
    for(auto it = G[on].begin();it != G[on].end();it++) {
        int id = *it;
        edge e = data[id];
        if(e.dst == parent) continue;
        int ans = remove_min(on ,e.dst ,target ,min(id ,mini));
        if(ans != -1) {
            if(id == ans) G[on].erase(it);
            return ans;
        }
    }
    return -1;
}
int main() {
    int N ,M;
    int i;
    while(cin >> N >> M) {
        for(i = 0;i < M;i++) cin >> data[i].src >> data[i].dst >> data[i].val;
        sort(data ,data + M ,cmp);

    }
}
