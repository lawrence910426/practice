#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
const int MAXN = 1e3 + 5 ,SIZE = 3e3;
vector<int> G[SIZE][2];
int ans;
bitset<SIZE> visit;
void dfs(int on ,int L ,bool type) {
    if(type == false) {
        for(int V : G[on][0]) {
            if(!visit[V] && G[V][1].size() == 0)
                ans = max(ans ,L + 1);
            if(!visit[V]) visit[V] = true ,dfs(V ,L + 1 ,!type) ,visit[V] = false;
        }
    } else {
        for(int V : G[on][1]) {
            if(!visit[V]) visit[V] = true ,dfs(V ,L + 1 ,!type) ,visit[V] = false;
        }
    }
}
int main() {
    int N ,M ,K ,L;
    int i ,src ,dst ,val;
    while(cin >> N >> M >> K >> L) {
        for(i = 0;i < SIZE;i++) G[i][0] = G[i][1] = vector<int>();
        while(K--) {
            cin >> src >> dst >> val;
            dst += MAXN;
            G[src][val].push_back(dst);
            G[dst][val].push_back(src);
        }
        ans = -1;
        visit.reset();
        for(i = 0;i < SIZE;i++) if(G[i][1].size() == 0) visit[i] = true ,dfs(i ,0 ,false) ,visit[i] = false;
        cout << ans << endl;
    }
}
