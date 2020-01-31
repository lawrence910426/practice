#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <assert.h>

using namespace std;
const int MAXN = 5e5 + 50;
const long long INF = 1LL << 45;
struct edge { int src ,dst; long long weight; };
struct seg { int l ,r ,code; } st[MAXN];
int seg_counter ,code_counter;

int N ,Q ,S ,root1 ,root2;
vector<edge> G[MAXN];
void AddEdge(int src ,int dst ,long long weight) { G[src].push_back(edge{src ,dst ,weight}); }
int build(int L ,int R ,int id ,int type) {
    if(L == R - 1) {
        st[id].code = L;
        st[id].l = st[id].r = -1;
    } else {
        int left = build(L ,(L + R) / 2 ,seg_counter++ ,type);
        int right = build((L + R) / 2 ,R ,seg_counter++ ,type);
        st[id].code = code_counter++;
        st[id].l = left;
        st[id].r = right;
        if(type == 1) {
            AddEdge(st[id].code ,st[left].code ,0);
            AddEdge(st[id].code ,st[right].code ,0);
        } else {
            AddEdge(st[left].code ,st[id].code ,0);
            AddEdge(st[right].code ,st[id].code ,0);
        }
    }
    return id;
}

void modify(int L ,int R ,int id ,int type ,int pos ,int l ,int r ,long long weight) {
    if(r <= L || R <= l) return;
    if(l <= L && R <= r) {
        if(type == 1) AddEdge(pos ,st[id].code ,weight);
        if(type == 2) AddEdge(st[id].code ,pos ,weight);
    } else {
        modify(L ,(L + R) / 2 ,st[id].l ,type ,pos ,l ,r ,weight);
        modify((L + R) / 2 ,R ,st[id].r ,type ,pos ,l ,r ,weight);
    }
}

long long dis[MAXN];
void spfa() {
    int i;
    for(i = 0;i < MAXN;i++) dis[i] = (i == S ? 0 : INF);
    queue<int> Q;
    for(Q.push(S);!Q.empty();Q.pop()) {
        int pos = Q.front();
        for(edge e : G[pos]) {
            if(dis[e.dst] > dis[e.src] + e.weight) {
                dis[e.dst] = dis[e.src] + e.weight;
                Q.push(e.dst);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int t ,v ,u ,l ,r;
    int i;
    long long w;
    while(cin >> N >> Q >> S) {
        S -= 1;
        for(i = 0;i < MAXN;i++) G[i] = vector<edge>();
        seg_counter = 0; code_counter = N;
        root1 = build(0 ,N ,seg_counter++ ,1);
        root2 = build(0 ,N ,seg_counter++ ,2);
        while(Q--) {
            cin >> t;
            if(t == 1) {
                cin >> v >> u >> w;
                v -= 1 ,u -= 1;
                AddEdge(v ,u ,w);
            } else {
                cin >> v >> l >> r >> w;
                v -= 1 ,l -= 1;
                if(t == 2) modify(0 ,N ,root1 ,1 ,v ,l ,r ,w);
                if(t == 3) modify(0 ,N ,root2 ,2 ,v ,l ,r ,w);
            }
        }
        spfa();
        for(i = 0;i < N;i++) cout << (dis[i] >= INF ? -1 : dis[i]) << " ";
        cout << endl;
    }
}
