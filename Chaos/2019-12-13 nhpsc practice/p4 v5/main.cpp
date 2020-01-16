#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
const int MAXN = 1e3 + 5;
bitset<MAXN> entry_a ,entry_b ,visit;
vector<pair<int ,bool> > A[MAXN] ,B[MAXN];
int N ,M ,K ,L ,ans;
void dfs(int on ,int L ,bool type) {
    if(type == false) {
        for(int V : A[on])
    } else {

    }
}

int main() {
    int i ,src ,dst ,val;
    while(cin >> N >> M >> K >> L) {
        for(i = 0;i < MAXN;i++) A[i] = B[i] = vector<pair<int ,bool> >();
        entry_a.reset() ,entry_a.flip() ,entry_b.reset() ,entry_b.flip();
        while(K--) {
            cin >> src >> dst >> val;
            if(val == 1) entry_a[src] = entry_b[dst] = false;
            A[src].push_back(pair<int ,int>(dst ,val == 1));
            B[dst].push_back(pair<int ,int>(src ,val == 1));
        }
        ans = -1;
        for(i = 1;i <= N;i++) for(auto edge : A[i]) {
            if(entry[i] && entry[V] && !edge.second) ans = max(ans ,1);
            if(entry[i] && entry[V] && !edge.second && !visit[edge.second])
                visit[edge.second] = true ,dfs(edge.second ,0 ,true) ,visit[edge.second] = false;
        }
    }
}
