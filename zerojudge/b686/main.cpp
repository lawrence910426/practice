#include <iostream>
#include <memory.h>
#include <algorithm>
using namespace std;
const int MAXN = 500;
int edge[MAXN][MAXN] ,floyd[MAXN][MAXN];
pair<int ,int> alarm[MAXN];
struct query {
    int code ,ans ,src ,dst ,alarm;
}Q[200005];

bool sort_alarm(query q1 ,query q2) { return q1.alarm > q2.alarm; }
bool sort_code(query q1 ,query q2) { return q1.code < q2.code; }
bool sort_pair(pair<int ,int> p1 ,pair<int ,int> p2) { return p1 > p2; }

int main() {
    int N ,M ,R;
    int alarm_ptr ,query_ptr ,i ,j ,k ,src ,dst ,val;
    while(cin >> N >> M >> R) {
        memset(edge ,-1 ,sizeof(edge));
        memset(floyd ,-1 ,sizeof(floyd));
        for(i = 0;i < N;i++) floyd[i][i] = 0;
        for(i = 0;i < N;i++) {
            cin >> alarm[i].first;
            alarm[i].second = i;
        }
        sort(alarm ,alarm + N ,sort_pair);
        while(M--) {
            cin >> src >> dst >> val;
            src -= 1, dst -= 1;
            edge[src][dst] = (edge[src][dst] == -1 ? val : min(edge[src][dst], val));
            edge[dst][src] = (edge[dst][src] == -1 ? val : min(edge[dst][src], val));
        }
        for(i = 0;i < R;i++) {
            cin >> src >> dst >> val;
            src -= 1 ,dst -= 1;
            Q[i].code = i ,Q[i].ans = 0;
            Q[i].src = src ,Q[i].dst = dst ,Q[i].alarm = val;
        }
        sort(Q ,Q + R ,sort_alarm);
        for(query_ptr = alarm_ptr = 0;alarm_ptr < N;alarm_ptr++) {
            for(;query_ptr < N;query_ptr++) {
                if(Q[query_ptr].alarm <= alarm[alarm_ptr].first) break;
                Q[query_ptr].ans = floyd[Q[query_ptr].src][Q[query_ptr].dst];
            }
            k = alarm[alarm_ptr].second;
            for(i = 0;i < N;i++) {
                if(edge[i][k] == -1 || edge[k][i] == -1) continue;
                if(floyd[i][k] == -1) floyd[i][k] = edge[i][k];
                else floyd[i][k] = min(floyd[i][k] ,edge[i][k]);
                if(floyd[k][i] == -1) floyd[k][i] = edge[k][i];
                else floyd[k][i] = min(floyd[k][i] ,edge[k][i]);
            }
            for(i = 0;i < N;i++) for(j = 0;j < N;j++) {
                if(floyd[i][k] == -1 || floyd[k][j] == -1) continue;
                if(floyd[i][j] == -1 || floyd[i][j] > floyd[i][k] + floyd[k][j]) {
                    floyd[i][j] = floyd[i][k] + floyd[k][j];
                }
            }
        }
        for(;query_ptr < N;query_ptr++)
            Q[query_ptr].ans = floyd[Q[query_ptr].src][Q[query_ptr].dst];
        sort(Q ,Q + R ,sort_code);
        for(i = 0;i < R;i++) cout << Q[i].ans << endl;
    }
}
/*
6 5 5
5 4 1 3 2 6

1 3 3
1 4 1
2 4 6
2 5 1
3 5 2

1 1 2
2 1 2
3 1 2
4 1 2
1 5 3
*/
// i quit
