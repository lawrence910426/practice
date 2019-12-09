#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
const int MAXN = 1e5;
vector<int> G[MAXN];
struct node {
    vector<int> kids;
    int parent ,top;
    long long method ,siz;
} tree[MAXN];
bitset<MAXN> visit;
int data[MAXN] ,N;

void dfs(int on ,int parent) {
    visit[on] = true;
    if(parent == -1) tree[on].top = on;
    tree[on].siz = 1;
    tree[on].parent = parent;
    for(int V : G[on]) if(V != parent && !visit[V]) {
        tree[V].top = tree[on].top;
        dfs(V ,on);
        tree[on].siz += tree[V].siz;
        tree[on].kids.push_back(V);
    }
}

int main() {
    int left ,right ,conn ,ans;
    int i ,j ,k;
    cin >> N;
    for(i = 0;i < MAXN;i++) G[i] = vector<int>();
    for(i = 0;i < N;i++) cin >> data[i];
    for(i = 0;i < N;i++) {
        left = right = -1;
        for(j = i - 1;j >= 0;j--) if(data[j] > data[i]) { left = j; break; }
        for(j = i + 1;j < N;j++) if(data[j] > data[i]) { right = j; break; }
        if(left == -1 && right == -1) continue;
        if(left == -1 && right != -1) conn = right;
        if(left != -1 && right == -1) conn = left;
        if(left != -1 && right != -1) conn = (data[left] > data[right] ? right : left);
        G[i].push_back(conn) ,G[conn].push_back(i);
    }
    visit.reset();
    for(i = 0;i < N;i++) if(!visit[i]) dfs(i ,-1);
    for(i = 0;i < N;i++) {
        vector<long long> sizes;
        if(tree[i].parent != -1) sizes.push_back(tree[tree[i].top].siz - tree[i].siz);
        for(int V : tree[i].kids) sizes.push_back(tree[V].siz);
        tree[i].method = (tree[tree[i].top].siz - 1) * 2;
        for(j = 0;j < sizes.size();j++) for(k = 0;k < sizes.size();k++) if(j != k) tree[i].method += sizes[j] * sizes[k];
    }
    for(ans = i = 0;i < N;i++) if(tree[ans].method < tree[i].method) ans = i;
    cout << tree[ans].method << " " << ans + 1 << endl;
}
