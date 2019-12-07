#pragma GCC optimize("Ofast")
#include <iostream>
#include <deque>
#include <bitset>
#include <vector>

using namespace std;
const int MAXN = 1e6 + 5;
int data[MAXN] ,left_idx[MAXN] ,right_idx[MAXN] ,N;
struct node {
    int top ,parent;
    vector<int> kids;
    long long methods ,siz;
} tree[MAXN];
vector<int> G[MAXN];
bitset<MAXN> visit;
void dfs(int on ,int parent) {
    visit[on] = true;
    if(parent == -1) tree[on].top = on;
    tree[on].parent = parent;
    tree[on].siz = 1;
    for(int V : G[on]) if(!visit[V] && V != parent) {
        tree[V].top = tree[on].top;
        dfs(V ,on);
        tree[on].siz += tree[V].siz;
        tree[on].kids.push_back(V);
    }
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,j ,k ,conn ,ans;
    cin >> N;
    for(i = 0;i < MAXN;i++) G[i] = vector<int>();
    visit.reset();
    for(i = 0;i < N;i++) cin >> data[i];
    deque<int> monotone;
    for(i = 0;i < N;i++) {
        while(!monotone.empty() && data[monotone.back()] < data[i]) monotone.pop_back();
        if(monotone.empty()) left_idx[i] = -1;
        else left_idx[i] = monotone.back();
        monotone.push_back(i);
    }
    monotone = deque<int>();
    for(i = N - 1;i >= 0;i--) {
        while(!monotone.empty() && data[monotone.front()] < data[i]) monotone.pop_front();
        if(monotone.empty()) right_idx[i] = -1;
        else right_idx[i] = monotone.front();
        monotone.push_front(i);
    }
    for(i = 0;i < N;i++) {
        if(left_idx[i] == -1 && right_idx[i] == -1) continue;
        if(left_idx[i] == -1 && right_idx[i] != -1) conn = right_idx[i];
        if(left_idx[i] != -1 && right_idx[i] == -1) conn = left_idx[i];
        if(left_idx[i] != -1 && right_idx[i] != -1) conn = (data[left_idx[i]] > data[right_idx[i]] ? right_idx[i] : left_idx[i]);
        G[i].push_back(conn) ,G[conn].push_back(i);
    }
    for(i = 0;i < N;i++) if(!visit[i]) dfs(i ,-1);
    for(i = 0;i < N;i++) {
        vector<long long> sz;
        if(tree[i].parent != -1) sz.push_back(tree[tree[i].top].siz - tree[i].siz);
        for(int V : tree[i].kids) sz.push_back(tree[V].siz);
        tree[i].methods = (tree[tree[i].top].siz - 1) * 2;
        for(j = 0;j < sz.size();j++) for(k = 0;k < sz.size();k++) if(j != k) tree[i].methods += sz[j] * sz[k];
    }
    for(ans = i = 0;i < N;i++) if(tree[ans].methods < tree[i].methods) ans = i;
    cout << tree[ans].methods << " " << ans + 1 << '\n';
}
