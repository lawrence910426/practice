#include <iostream>
#include <vector>
#include <bitset>
#include <memory.h>

using namespace std;
#define MAXN 100005
#define MAXL 20
int parent[MAXN][20] ,depth[MAXN] ,increase[MAXN][MAXL][2] ,decrease[MAXN][MAXL][2];
vector<pair<int ,int> > graph[MAXN];
bitset<MAXN> visit;

void dfs(int pa ,int on ,int w) {
    if(visit[on]) return;
    visit[on] = true;
    depth[on] = depth[pa] + 1;
    parent[on][0] = pa;
    decrease[on][0][0] = increase[on][0][0] = decrease[on][0][1] = increase[on][0][1] = w;
    for(int i = 0;i < MAXL - 1;i++) {
        int parent_pos = parent[on][i];
        parent[on][i + 1] = parent[parent_pos][i];
        if(increase[on][i][0] != -1 && increase[parent_pos][i][0] != -1 && increase[on][i][1] <= increase[parent_pos][i][0]) {
            increase[on][i + 1][0] = increase[on][i][0];
            increase[on][i + 1][1] = increase[parent_pos][i][1];
        } else increase[on][i + 1][0] = increase[on][i + 1][1] = -1;
        if(decrease[on][i][0] != -1 && decrease[parent_pos][i][0] != -1 && decrease[on][i][1] >= decrease[parent_pos][i][0]) {
            decrease[on][i + 1][0] = decrease[on][i][0];
            decrease[on][i + 1][1] = decrease[parent_pos][i][1];
        } else decrease[on][i + 1][0] = decrease[on][i + 1][1] = -1;
    }
    for(auto value : graph[on]) dfs(on ,value.first ,value.second);
}

#define lowbit(x) (x & (-x))
bool a_dec ,a_inc ,b_dec ,b_inc;
int preva ,prevb ,a ,b;

inline void update(int jump) {
    a_dec &= decrease[a][jump][0] != -1 && (preva == -1 || preva >= decrease[a][jump][0]);
    a_inc &= increase[a][jump][0] != -1 && (preva == -1 || preva <= increase[a][jump][0]);
    b_dec &= decrease[b][jump][0] != -1 && (prevb == -1 || prevb >= decrease[b][jump][0]);
    b_inc &= increase[b][jump][0] != -1 && (prevb == -1 || prevb <= increase[b][jump][0]);
    if(a_dec) preva = decrease[a][jump][1];
    if(a_inc) preva = increase[a][jump][1];
    if(b_dec) prevb = decrease[b][jump][1];
    if(b_inc) prevb = increase[b][jump][1];
    a = parent[a][jump] ,b = parent[b][jump];
}

inline bool able() {
    preva = prevb = -1;
    a_dec = b_dec = a_inc = b_inc = true;
    if(depth[a] < depth[b]) swap(a ,b);
    for(int diff = depth[a] - depth[b];diff > 0;diff -= lowbit(diff)) {
        int jump = __lg(lowbit(diff));
        a_dec &= decrease[a][jump][0] != -1 && (preva == -1 || preva >= decrease[a][jump][0]);
        a_inc &= increase[a][jump][0] != -1 && (preva == -1 || preva <= increase[a][jump][0]);
        if(a_dec) preva = decrease[a][jump][1];
        if(a_inc) preva = increase[a][jump][1];
        a = parent[a][jump];
    }
    for(int i = MAXL - 1;i >= 0;i--) if(parent[a][i] != parent[b][i]) update(i);
    if(a == b) {
        return a_dec || a_inc;
    } else {
        update(0);
        return (a_dec && b_inc && preva >= prevb) || (a_inc && b_dec && preva <= prevb);
    }
}

int main() {
    int N ,Q;
    int value ,i;
    while(cin >> N >> Q) {
        memset(parent ,0 ,sizeof(parent));
        memset(depth ,0 ,sizeof(depth));
        memset(increase ,-1 ,sizeof(increase));
        memset(decrease ,-1 ,sizeof(decrease));
        for(i = 0;i < N - 1;i++) {
            cin >> a >> b >> value;
            graph[a].push_back(pair<int ,int>(b ,value));
            graph[b].push_back(pair<int ,int>(a ,value));
        }
        visit.reset();
        dfs(1 ,1 ,-1);
        while(Q--) {
            cin >> a >> b;
            cout << (able() ? "YES" : "NO") << endl;
        }
    }
}
