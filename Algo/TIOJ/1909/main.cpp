#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;
const int MAXN = 1e5 + 5 ,MAXL = 30;
/*--------------------------------------------------------------------*/
#pragma region RMQ
int N;
int data[MAXN] ,RMQ[MAXN][MAXL];
inline int query(int L ,int R) {
    int len = __lg(R - L);
    return max(RMQ[L][len] ,RMQ[R - (1 << len)][len]);
}
inline void init_RMQ() {
    int i ,j ,ptr;
    for(i = 0;i < N;i++) RMQ[i][0] = data[i];
    for(j = 1;j < MAXL;j++) for(i = 0;i < N;i++) {
        ptr = min(N ,i + (1 << (j - 1)));
        RMQ[i][j] = max(RMQ[i][j - 1] ,RMQ[ptr][j - 1]);
    }
}
inline void get_ans(int on ,int& lans ,int& rans) {
    int L ,R ,mid;
    if(on != 0) {
        L = 0 ,R = on;
        if(query(L ,R) < data[on]) lans = -1;
        else {
            while(L != R - 1) {
                mid = (L + R) / 2;
                if(query(mid ,R) > data[on]) L = mid;
                else R = mid;
            }
            lans = L;
        }
    } else lans = -1;
    if(on != N - 1) {
        L = on + 1 ,R = N;
        if(query(L ,R) < data[on]) rans = -1;
        else {
            while(L != R - 1) {
                mid = (L + R) / 2;
                if(query(L ,mid) > data[on]) R = mid;
                else L = mid;
            }
            rans = L;
        }
    }
}
#pragma endregion RMQ
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
#pragma region methods
struct node {
    vector<int> kids;
    long long methods ,siz;
    int parent ,top;
} tree[MAXN];
vector<int> G[MAXN];
bitset<MAXN> visit;
void dfs(int on ,int parent) {
    visit[on] = true;
    tree[on].parent = parent;
    tree[on].siz = 1;
    if(parent == -1) tree[on].top = on;
    for(int V : G[on]) if(V != parent && !visit[V]) {
        tree[on].kids.push_back(V);
        tree[V].top = tree[on].top;
        dfs(V ,on);
        tree[on].siz += tree[V].siz;
    }
}
void methods() {
    int i ,j ,k;
    for(i = 0;i < N;i++) {
        vector<long long> sizes;
        if(tree[i].parent != -1) sizes.push_back(tree[tree[i].top].siz - tree[i].siz);
        for(int V : tree[i].kids) sizes.push_back(tree[V].siz);
        tree[i].methods = (tree[tree[i].top].siz - 1) * 2;
        for(j = 0;j < sizes.size();j++) for(k = 0;k < sizes.size();k++) if(j != k) tree[i].methods += sizes[j] * sizes[k];
    }
}
#pragma endregion methods
/*--------------------------------------------------------------------*/

int main() {
    int i ,left ,right ,connect ,before ,after ,ans;
    cin >> N;
    for(i = 0;i < N;i++) cin >> data[i];
    init_RMQ();
    for(i = 0;i < MAXN;i++) G[i] = vector<int>();
    for(i = 0;i < N;i++) {
        get_ans(i ,left ,right);
        if(left == -1 && right == -1) continue;
        if(left == -1 && right != -1) connect = right;
        if(left != -1 && right == -1) connect = left;
        if(left != -1 && right != -1) connect = (data[left] > data[right] ? right : left);
        before = min(connect ,i) ,after = max(connect ,i);
        G[before].push_back(after), G[after].push_back(before);
    }
    visit.reset();
    for(i = 0;i < N;i++) if(!visit[i]) dfs(i ,-1);
    methods();
    for(ans = i = 0;i < N;i++) if(tree[ans].methods < tree[i].methods) ans = i;
    for(i = 0;i < N;i++) cout << i << " " << tree[i].methods << endl;
    cout << tree[ans].methods << " " << ans + 1 << endl;
}
