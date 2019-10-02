#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <memory.h>
#include <vector>
#include <bitset>
#include <assert.h>

#define MAXN 500005
#define MAXL 30

using namespace std;
int dsu[MAXN];
int boss(int i) { return (i == dsu[i] ? i : dsu[i] = boss(dsu[i])); }
void join(int a ,int b) { dsu[boss(a)] = dsu[boss(b)]; }

vector<pair<int ,int> > graph[MAXN];
bitset<MAXN> visit ,output;
int ancestor[MAXN][MAXL] ,maximum[MAXN][MAXL] ,depth[MAXN] ,inputs[MAXN][2];
int N ,M;

void dfs(int parent ,int on ,int value) {
    assert(0 <= on && on < MAXN);
    assert(0 <= parent && parent < MAXN);
    if(visit[on]) return;
    visit[on] = true;
    if(parent == on) depth[on] = 0;
    else depth[on] = depth[parent] + 1;
    ancestor[on][0] = parent;
    maximum[on][0] = value;

    ///assert(depth[on] <= 300000);

    int pos = parent ,layer = 0;
    while(layer < MAXL - 1) {
        assert(0 <= layer && layer + 1 < MAXL);
        assert(0 <= pos && pos < MAXN);

        ancestor[on][layer + 1] = ancestor[pos][layer];
        maximum[on][layer + 1] = max(maximum[on][layer] ,maximum[pos][layer]);
        pos = ancestor[pos][layer];
        layer += 1;
    }
    for(auto P : graph[on]) dfs(on ,P.first ,P.second);
}

void preprocess() {
    memset(ancestor ,-1 ,sizeof(ancestor));
    memset(maximum ,-1 ,sizeof(maximum));
    memset(depth ,-1 ,sizeof(depth));
    visit.reset();
    for(int i = 1;i <= N;i++) dfs(i ,i ,-1);
}

#define lowbit(x) (x & (-x))
int get_ans(int a, int b) {
    int maxi = -1 ,diff ,jump;
    if(depth[a] < depth[b]) swap(a ,b);
    for(diff = depth[a] - depth[b];diff != 0;diff -= lowbit(diff)) {
        jump = __lg(lowbit(diff));
        maxi = max(maxi ,maximum[a][jump]);
        a = ancestor[a][jump];
    }
    for(int i = __lg(depth[a]);i >= 0;i--) if(ancestor[a][i] != ancestor[b][i]) {
        maxi = max(maxi ,maximum[a][i]);
        maxi = max(maxi ,maximum[b][i]);
        a = ancestor[a][i];
        b = ancestor[b][i];
    }
    if(a != b) {
        maxi = max(maxi ,maximum[a][0]);
        maxi = max(maxi ,maximum[b][0]);
    }
    return maxi;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,a ,b;
    cin >> N >> M;
    output.reset();
    for(i = 1;i <= N;i++) dsu[i] = i;
    for(i = 1;i <= M;i++) {
        cin >> a >> b;
        if(boss(a) != boss(b)) {
            join(a ,b);
            graph[a].push_back(pair<int ,int>(b ,i));
            graph[b].push_back(pair<int ,int>(a ,i));
        } else {
            output[i] = true;
            inputs[i][0] = a;
            inputs[i][1] = b;
        }
    }
    preprocess();
    for(i = 1;i <= M;i++) {
        if(output[i]) cout << get_ans(inputs[i][0] ,inputs[i][1]) << '\n';
        else cout << "Mukyu" << '\n';
    }
    //cout << endl;
}

/*
3 4
1 2
2 3
1 3
1 2

2 3
2 1
1 2
2 1

6 8
1 2
2 1
1 3
4 3
3 2
3 5
1 5
1 4
*/
