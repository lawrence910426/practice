#include <assert.h>
#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>

using namespace std;
struct edge {
    int capacity ,cost ,flow;
    int from ,dest;
    vector<edge>::iterator rev;
};

vector<edge> Graph[10000]; //0-source ,1-destination
long long int dist[10000]; //distance. -1 means unreachable
edge* previous[10000];     //where the edge comes from
bool visit[10000];         //visit[value]: return (value in queue)

void bellman_ford() {
    memset(dist ,-1 ,sizeof(dist));
    memset(visit ,0 ,sizeof(visit));
    for(int i = 0;i < 10000;i++) previous[i] = nullptr;

    queue<int> pos;
    visit[0] = true ,dist[0] = 0;
    for(pos.push(0);!pos.empty();pos.pop()) {
        visit[pos.front()] = false;
        for(int i = 0;i < Graph[pos.front()].size();i++) {
            edge e = Graph[pos.front()][i];
            if(e.flow == e.capacity) continue;
            if(dist[e.dest] == -1 || dist[e.dest] > dist[e.from] + e.cost) {
                dist[e.dest] = dist[e.from] + e.cost;
                previous[e.dest] = &(Graph[pos.front()][i]);
                if(!visit[e.dest]) {
                    visit[e.dest] = true;
                    pos.push(e.dest);
                }
            }
        }
    }
}

pair<long long int ,long long int> MinCostMaxFlow() {
    long long int flow = 0 ,cost = 0 ,bottle_neck;
    edge* tmp;
    while(true) {
        bellman_ford();
        if(dist[1] == -1) return pair<int ,int>(flow ,cost); //nothing left in the resisdual network
        bottle_neck = (1LL << 31) - 1;
        for(tmp = previous[1]; tmp != nullptr ; tmp = previous[tmp->from]) //iterate from destination(1) to origin(0)
            bottle_neck = (bottle_neck > tmp->capacity - tmp->flow ? tmp->capacity - tmp->flow : bottle_neck);
        flow += bottle_neck;
        for(tmp = previous[1]; tmp != nullptr ; tmp = previous[tmp->from]) {
            tmp->flow += bottle_neck;
            tmp->rev->flow -= bottle_neck;
            cost += tmp->cost * bottle_neck;
        }
    }
}

void insert_edge(edge e) {
    edge tmp;
    tmp.from = e.dest;
    tmp.dest = e.from;
    tmp.capacity = e.capacity;
    tmp.flow = e.capacity;
    tmp.cost = -e.cost;
    Graph[e.from].push_back(e);
    Graph[tmp.from].push_back(tmp);
    (--Graph[e.from].end())->rev = --Graph[tmp.from].end();
    (--Graph[tmp.from].end())->rev = --Graph[e.from].end();
}

int numbers[5000][2];
int main() {
    int N;
    int i, j, k;
    edge tmp;
    for(auto v : Graph) v = vector<edge>();

    cin >> N;
    for(i = 0;i < N;i++) cin >> numbers[i][0] >> numbers[i][1];
    for(i = 0;i < N - 1;i++) {
        for(j = 0;j < 2;j++) for(k = 0;k < 2;k++) {
            tmp.cost = (numbers[i][j] <= numbers[i + 1][k] ? 0 : 1);
            tmp.from = i + N * j + 500;
            tmp.dest = (i + 1) + N * k + 500;
            tmp.capacity = 1;
            tmp.flow = 0;
            insert_edge(tmp);
        }
    }
    tmp.from = 0 ,tmp.dest = 2 ,tmp.capacity = 1 ,tmp.cost = 0 ,tmp.flow = 0; insert_edge(tmp);
    tmp.from = 2 ,tmp.dest = 500 ,tmp.capacity = 1 ,tmp.cost = 0 ,tmp.flow = 0; insert_edge(tmp);
    tmp.from = 2 ,tmp.dest = 500 + N ,tmp.capacity = 1 ,tmp.cost = 0 ,tmp.flow = 0; insert_edge(tmp);
    tmp.from = 500 + N - 1 ,tmp.dest = 1 ,tmp.capacity = 1 ,tmp.cost = 0 ,tmp.flow = 0; insert_edge(tmp);
    tmp.from = 500 + N + N - 1 ,tmp.dest = 1 ,tmp.capacity = 1 ,tmp.cost = 0 ,tmp.flow = 0; insert_edge(tmp);

    auto ans = MinCostMaxFlow();
    assert(ans.first == 1);
    cout << ans.second << '\n';
}
