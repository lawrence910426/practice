#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <algorithm>
#include <vector>
#define lowbit(x) (x & (-x))
using namespace std;
const int MAXN = 1e5 + 50 ,MAXL = 20 ,root = 0;
int parent[MAXN][MAXL] ,depth[MAXN];
long long weight[MAXN][MAXL];
vector<pair<int ,int> > G[MAXN];
void prebuild(int on ,int par ,int dep ,int wei) {
    int i;
    parent[on][0] = par;
    weight[on][0] = wei;
    depth[on] = dep;
    for(i = 1;i < MAXL;i++) parent[on][i] = parent[parent[on][i - 1]][i - 1];
    for(i = 1;i < MAXL;i++) weight[on][i] = weight[on][i - 1] + weight[parent[on][i - 1]][i - 1];
    for(auto edge : G[on]) if(edge.first != par) prebuild(edge.first ,on ,dep + 1 ,edge.second);
}
long long dis(int a ,int b) {
    long long ans = 0;
    int diff ,i;
    if(depth[a] > depth[b]) swap(a ,b);
    diff = depth[b] - depth[a];
    while(diff) {
        ans += weight[b][__lg(lowbit(diff))];
        b = parent[b][__lg(lowbit(diff))];
        diff -= lowbit(diff);
        //cout << depth[a] << " " << depth[b] << " " << ans << endl;
    }
    while(a != b) {
        for(i = MAXL - 1;i >= 0 && parent[a][i] == parent[b][i];i--) ;
        if(i == -1) {
            ans += weight[a][0] + weight[b][0];
            break;
        } else {
            ans += weight[a][i] + weight[b][i];
            a = parent[a][i] ,b = parent[b][i];
        }
        //cout << depth[a] << " " << depth[b] << " " << ans << endl;
    }
    return ans;
}

int S[MAXN];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,K ,siz;
    int i ,src ,dst ,w;
    long long ans ,sum ,out;
    while(cin >> N >> K) {
        for(i = 0;i < N - 1;i++) {
            cin >> src >> dst >> w;
            G[src].push_back(pair<int ,int>(dst ,w));
            G[dst].push_back(pair<int ,int>(src ,w));
        }
        prebuild(root ,root ,0 ,0);
        out = 0;
        while(K--){
            cin >> siz;
            for(i = 0;i < siz;i++) cin >> S[i];
            sort(S ,S + siz);
            ans = (1LL << 31) - 1;
            do {
                sum = 0;
                for(i = 0;i < siz - 1;i++) {
                    //cout << S[i] << " ";
                    sum += dis(S[i] ,S[i + 1]);
                }
                //cout << "Sum " << sum << endl;
                ans = min(ans ,sum);
            } while(next_permutation(S ,S + siz));
            //cout << ans << endl;
            out += ans;
        }
        cout << out << '\n';
    }
}
/*
8 5
6 1 4
1 4 1
1 5 1
1 0 3
0 2 5
3 0 2
0 7 1
2 1 6
2 3 2
3 6 1 5

2 3 5
2 7 4
5 7 2 1 5 6

8 2
6 1 4
1 4 1
1 5 1
1 0 3
0 2 5
3 0 2
0 7 1
2 3 5
*/
