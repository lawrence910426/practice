#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;
const int MAXN = 1e5 + 50;
struct E { int src ,dst ,val; } edge[MAXN];
vector<int> G[MAXN];

int main() {
    int N ,i ,used;
    while(cin >> N) {
        memset(edge ,-1 ,sizeof(edge)); used = 0;
        for(i = 1;i <= N;i++) G[i] = vector<int>();
        for(i = 0;i < N - 1;i++) {
            cin >> edge[i].src >> edge[i].dst;
            G[edge[i].src].push_back(i);
            G[edge[i].dst].push_back(i);
        }
        for(i = 1;i <= N;i++) if(G[i].size() >= 3) {
            for(int code : G[i]) edge[code].val = used++;
            break;
        }
        for(i = 0;i < N - 1;i++) if(edge[i].val == -1) edge[i].val = used++;
        for(i = 0;i < N - 1;i++) cout << edge[i].val << endl;
    }
}
