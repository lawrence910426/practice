#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;
const int MAXM = 5e4 + 50 ,MAXN = 3e2 + 5 ,INF = (1LL << 31) - 1;
struct e { int src, dst ,weight ,code; } edge[MAXM];
bool cmp(e a ,e b) { return a.weight < b.weight; }
vector<list<int> > G[MAXN];
int dfs(int pos ,int target ,int mini) {
    if(pos == target) return mini;
    for(int i = 0;i < G[pos].size();i++) {
        e tmp = edge[*G[pos][i].begin()];
        int ans = dfs(tmp.dst ,target ,min(mini ,tmp.code));
        if(mini == tmp.code) {
            G[pos][i].push_back(tmp.code);
            return mini;
        }
    }
    return INF;
}
struct dsu {
    int data[MAXN];
    dsu() { for(int i = 0;i < MAXN;i++) data[i] = i; }
    int query(int i) { return (data[i] == i ? i : data[i] = query(data[i]));}
    void join(int a ,int b) { data[query(a)] = data[query(b)]; }
};
int N ,M;
int main() {
    int i ,lptr ,rptr ,a ,b ,mini ,aa ,bb;
    while(cin >> N >> M) {
        for(i = 0;i < M;i++) cin >> edge[i].src >> edge[i].dst >> edge[i].weight;
        sort(edge ,edge + M ,cmp);
        for(rptr = 0;rptr < M;rptr++) {
            a = edge[rptr].src ,b = edge[rptr].dst;
            aa = boss(a) ,bb = boss(b);
            if(aa == bb) {
                dfs(a ,b ,INF);
            } else {

            }
        }
    }
}
