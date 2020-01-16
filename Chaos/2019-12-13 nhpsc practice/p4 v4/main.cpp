#include <iostream>
#include <vector>
#include <bitset>
#include <memory.h>
#include <assert.h>


using namespace std;
const int MAXN = 1005 ,MAXV = 3000;
vector<int> G_0[MAXV] ,G_1[MAXV];
bool has_0[MAXV][MAXV] ,has_1[MAXV][MAXV];
bitset<MAXN> visit ,entry;
int longest(int on ,int start) {
    int length = -1 ,result;
    for(int V : G_0[on]) {
        if(visit[V]) continue;
        visit[V] = true;
        if(!has_1[V][start]) {
            length = max(length ,1);
            // printf("%d %d %d L1\n" ,on ,V ,length);
        }
        for(int U : G_1[V]) {
            if(visit[U]) continue;
            visit[U] = true;
            // printf("%d %d %d %d in\n" ,on ,V ,U ,length);
            result = longest(U ,start);
            // printf("%d %d %d %d %d\n" ,on ,V ,U ,length ,result);
            if(result == -1) continue;
            length = max(length ,result + 2);
            visit[U] = false;
        }
        visit[V] = false;
    }
    return length;
}

int main() {
    int N ,M ,K ,L ,ans ,result;
    int i ,src ,dst ,val;
    while(cin >> N >> M >> K >> L) {
        for(i = 0;i < MAXV;i++) G_0[i] = G_1[i] = vector<int>();
        memset(has_0 ,0 ,sizeof(has_0)) ,memset(has_1 ,0 ,sizeof(has_1)) ,entry.reset() ,entry.flip();
        while(K--) {
            cin >> src >> dst >> val;
            dst += MAXN;
            if(val == 0) {
                G_0[src].push_back(dst);
                G_0[dst].push_back(src);
                has_0[src][dst] = has_0[dst][src] = true;
                entry[src] = entry[dst] = false;
            } else {
                G_1[src].push_back(dst);
                G_1[dst].push_back(src);
                has_1[src][dst] = has_1[dst][src] = true;
            }
        }
        visit.reset() ,ans = 0;
        for(i = 0;i < MAXV;i++) if( (1 <= i && i <= N) || (MAXN + 1 <= i && i <= MAXN + M) && entry[i]) {
            visit[i] = true;
            result = longest(i ,i);
            visit[i] = false;
            if(result == -1) continue;
            ans = max(ans ,result);
            // cout << ans << endl << endl;
        }
        cout << ans << endl;
    }
}
