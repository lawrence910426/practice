#include <iostream>
#include <bitset>
#include <memory.h>
#include <vector>

using namespace std;
const int MAXN = 300;
struct edge { int src ,dst ,flow ,cap ,cost; };
int N ,E ,src ,dst;
vector<edge> edges;
vector<edge> G[MAXN];

void AddEdge(int src ,int dst ,int cap ,int cost) {
    edge e1 = { src ,dst ,0 ,cap ,cost };
    edge e2 = { dst ,src ,0 ,0 ,-cost };
    edges.push_back(e1);
    G[src].push_back(edges.size() - 1);
    edges.push_back(e2);
    G[src].push_back(edges.size() - 1);
}

int main() {
    int src ,dst ,cap ,cost;
    while(cin >> N >> E >> src >> dst) {

    }
}
