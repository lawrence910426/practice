#include <iostream>
#include <vector>
#include <bitset>
#include <assert.h>
#define DBG ;

using namespace std;
const int MAXN = 1e4 ,MAXM = 1e3 + 5;
vector<int> G0[MAXN] ,G1[MAXN];
bitset<MAXN> visit ,has_1[MAXN] ,has_0[MAXN];
int M ,N ,K ,L;
int dfs(int on ,int root) {
    int length = -1 ,result;
    for(int V : G0[on]) {
        if(visit[V]) continue;
        visit[V] = true;
        if(!has_1[V][root]) length = max(length ,1);
        DBG printf("%d %d %d L1\n" ,on ,V ,length);
        for(int U : G1[V]) {
            if(visit[U]) continue;
            visit[U] = true;
            DBG printf("%d %d %d %d in\n" ,on ,V ,U ,length);
            result = dfs(U ,root);
            if(result == -1) continue;
            DBG printf("%d %d %d %d %d\n" ,on ,V ,U ,length ,result);
            length = max(length ,result + 2);
            visit[U] = false;
        }
        visit[V] = false;
    }
    assert(length <= L);
    return length;
}
int main() {
    int i ,src ,dst ,val ,ans ,result;
    while(cin >> M >> N >> K >> L) {
        for(i = 0;i < MAXN;i++) G0[i] = G1[i] = vector<int>() ,has_0[i].reset() ,has_1[i].reset();
        while(K--) {
            cin >> src >> dst >> val;
            dst += MAXM;
            if(val == 0) {
                G0[src].push_back(dst);
                G0[dst].push_back(src);
                has_0[src][dst] = has_0[dst][src] = true;
            } else {
                G1[src].push_back(dst);
                G1[dst].push_back(src);
                has_1[src][dst] = has_1[dst][src] = true;
            }
        }
        ans = -1;
        for(i = 0;i < MAXN;i++) if( (1 <= i && i <= M) || (MAXM + 1 <= i && i <= MAXM + M) ) {
            visit[i] = true;
            result = dfs(i ,i);
            visit[i] = false;
            DBG cout << result << endl << endl;
            ans = max(ans ,result);
        }
        cout << ans << endl;
    }
}
/*
2 2 2 2
1 2 0
1 2 1

5 5 5 5
1 2 0
2 2 1
2 3 0
4 3 1
4 5 0
*/
