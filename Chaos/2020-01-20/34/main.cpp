#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>

using namespace std;
const int MAXN = 2e5 + 50 ,root = 1 ,MAXL = 20;
struct node {
    int siz ,parent[MAXL] ,max_kid;
    vector<int> kid ,centroid;
} data[MAXN];
vector<int> G[MAXN];
void dfs(int on ,int parent) {
    int i;
    data[on].parent[0] = parent;
    for(i = 1;i < MAXL;i++) data[on].parent[i] = data[data[on].parent[i - 1]].parent[i - 1];
    data[on].siz = 1;
    for(i = 0;i < G[on].size();i++) if(G[on][i] != parent) {
        data[on].kid.push_back(G[on][i]);
        dfs(G[on][i] ,on);
        data[on].siz += data[G[on][i]].siz;
    }
    data[on].max_kid = 0;
    for(int K : data[on].kid) data[on].max_kid = max(data[on].max_kid ,data[K].siz);
}
int N;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int i ,j ,a ,b ,pos ,tmp;
    while(cin >> N) {
        for(i = 0;i < N - 1;i++) {
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        dfs(root ,root);
        for(i = 1;i <= N;i++) {
            pos = i;
            for(j = MAXL - 1;j >= 0;j--) {
                if(data[data[pos].parent[j]].siz >= 2 * data[i].max_kid) continue;
                else pos = data[pos].parent[j];
            }
            if(data[pos].siz < 2 * data[i].max_kid) pos = data[pos].parent[0];
            while(data[pos].siz >= 2 * data[i].max_kid && data[i].siz * 2 >= data[pos].siz) {
                data[pos].centroid.push_back(i);
                if(pos == root) break;
                pos = data[pos].parent[0];
            }
        }
        for(i = 1;i <= N;i++) {
            for(int item : data[i].centroid) cout << item << " ";
            cout << '\n';
        }
    }
}
