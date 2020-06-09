#include <iostream>
#include <queue>
#include <memory.h>
#define min2(a ,b) ((a) > (b) ? (b) : (a))
using namespace std;

struct edge {
    int capacity ,flow ,cost ,source ,dest;
};

edge E[2005][2005][2];
vector<edge*> G[2005];  //2001-source ,2002-dest
#define SS 2001
#define SD 2002

int dis[2005];
edge* from[2005];
bool visit[2005];
void bellman_ford() {
    queue<int> next;
    memset(dis ,-1 ,sizeof(dis));
    memset(visit ,-1 ,sizeof(visit));
    dis[SS] = 0;
    for(int i = 0;i < 2005;i++) from[i] = nullptr;
    for(next.push(SS);!next.empty();next.pop()) {
        visit[next.front()] = false;
        for(edge* e : G[next.front()]) {
            if(e->flow >= e->capacity) continue;
            if(dis[e->dest] == -1 || dis[e->dest] > dis[e->source] + e->cost) {
                dis[e->dest] = dis[e->source] + e->cost;
                from[e->dest] = e;
                if(!visit[e->dest]) {
                    visit[e->dest] = true;
                    next.push(e->dest);
                }
            }
        }
    }
}

pair<long long int ,long long int> MinCostMaxFlow() {
    long long int cost = 0 ,flow = 0 ,bottle_neck;
    while(true) {
        bellman_ford();
        if(dis[SD] == -1) return pair<int ,int>(cost ,flow);
        bottle_neck = (1LL << 31) - 1;
        for(edge* e = from[SD];e != nullptr;e = from[e->source])
            bottle_neck = min2(bottle_neck ,e->capacity - e->flow);
        flow += bottle_neck;
        for(edge* e = from[SD];e != nullptr;e = from[e->source]) {
            e->flow += bottle_neck;
            E[e->dest][e->source][1].flow -= bottle_neck;
            cost += bottle_neck * e->cost;
        }
    }
}

void show(int on) {
    for(int i = 0;i < 2005;i++) {
        if(E[on][i][0].flow != 0 && E[on][i][0].capacity != 0) {
            printf("%d\t%d\t%d\n" ,E[on][i][0].source ,E[on][i][0].dest ,E[on][i][0].cost);
            show(E[on][i][0].dest);
        }
    }
}

void insert_edge(edge* e) {
    G[e->source].push_back(e);
    E[e->dest][e->source][1].capacity = e->capacity;
    E[e->dest][e->source][1].cost = -(e->cost);
    E[e->dest][e->source][1].flow = e->capacity - e->flow;
    E[e->dest][e->source][1].source = e->dest;
    E[e->dest][e->source][1].dest = e->source;
    G[e->dest].push_back(&(E[e->dest][e->source][1]));
}

int main() {
    int N ,L ,U ,K ,T ,x[1005] ,y[1005];
    int i ,j ,eax ,ebx;
    for(cin >> T;T--;) {
        cin >> N >> L >> U >> K;
        for(i = 0;i < N + N;i++) G[i] = vector<edge*>();
        for(i = 0;i < N + N;i++) for(j = 0;j < N + N;j++) E[i][j][0].capacity = 1;
        for(i = 0;i < K;i++) {
            cin >> eax >> ebx;
            E[eax - 1][N + ebx - 1][0].capacity = 0;
        }
        for(i = 0;i < N;i++) cin >> x[i];
        for(i = 0;i < N;i++) cin >> y[i];
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) {
            if(x[i] + y[j] < L) E[i][j + N][0].cost = 0;
            else if(U < x[i] + y[j]) E[i][j + N][0].cost = U - L;
            else E[i][j + N][0].cost = x[i] + y[j] - L;
            E[i][j + N][0].source = i ,E[i][j + N][0].dest = j + N ,E[i][j + N][0].flow = 0;
            insert_edge(&(E[i][j + N][0]));
        }
        for(i = 0;i < N;i++) {
            E[SS][i][0].source = SS;
            E[SS][i][0].dest = i;
            E[SS][i][0].capacity = 1;
            E[SS][i][0].flow = 0;
            E[SS][i][0].cost = 0;
            insert_edge(&(E[SS][i][0]));

            E[i + N][SD][0].source = i + N;
            E[i + N][SD][0].dest = SD;
            E[i + N][SD][0].capacity = 1;
            E[i + N][SD][0].flow = 0;
            E[i + N][SD][0].cost = 0;
            insert_edge(&(E[i + N][SD][0]));
        }
        pair<int ,int> ans = MinCostMaxFlow();
        //show(SS);
        if(ans.second == N) cout << ans.first << endl;
        else cout << "no" << endl;
    }
}
/*
2
5 2 100 0
4 1 3 2 5
9 8 7 10 6

5 2 100 5
1 1
1 2
1 3
1 4
1 5
4 1 3 2 5
9 8 7 10 6
*/

/*
3
5 6 100 0
1 7 8 9 10
1 2 3 4 5

5 6 100 1
1 5
1 7 8 9 10
1 2 3 4 5

5 6 100 2
1 4
1 5
1 7 8 9 10
1 2 3 4 5

*/
