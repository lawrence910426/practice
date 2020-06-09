#include <iostream>
#include <algorithm>
#include <map>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <memory.h>

#define MAXN 5050
const long long int src = 251 ,dest = 252 ,INF = (1LL << 31) - 1;
using namespace std;

long long int n, m, s = src, t = dest;
long long int u, v, c, w;
long long int maxFlow, minCost;

struct Edge
{
	long long int from, to, flow, cap, cost;
};

bool vis[MAXN];
long long int p[MAXN], a[MAXN], d[MAXN];
vector<long long int> g[MAXN];
vector<Edge> edges;

void init()
{
    maxFlow = minCost = 0;
	for (int i = 0; i <= MAXN; i++) g[i].clear();
	edges.clear();
	memset(vis ,0 ,sizeof(vis));
	memset(a ,0 ,sizeof(a));
	memset(d ,0 ,sizeof(d));
}
void addedge(long long int from, long long int to, long long int cap, long long int cost)
{
	Edge temp1 = { from, to, 0, cap, cost };
	Edge temp2 = { to, from, 0, 0, -cost };
	edges.push_back(temp1);
	edges.push_back(temp2);
	long long int len = edges.size();
	g[from].push_back(len - 2);
	g[to].push_back(len - 1);
}

bool bellmanford(long long int s, long long int t)
{
	for (long long int i = 0; i < MAXN; i++)
		d[i] = INF;
	d[s] = 0;
	memset(vis, false, sizeof(vis));
	memset(p, -1, sizeof(p));
	p[s] = -1;
	a[s] = INF;
	queue<long long int> que;
	que.push(s);
	vis[s] = true;
	while (!que.empty())
	{
		long long int u = que.front();
		que.pop();
		vis[u] = false;
		for (long long int i = 0; i < g[u].size(); i++)
		{
			Edge& e = edges[g[u][i]];
			if (e.cap > e.flow&&d[e.to] > d[u] + e.cost)
			{
				d[e.to] = d[u] + e.cost;
				p[e.to] = g[u][i];
				a[e.to] = min(a[u], e.cap - e.flow);
				if (!vis[e.to])
				{
					que.push(e.to);
					vis[e.to] = true;
				}
			}
		}
	}
	if (d[t] == INF)
		return false;
	maxFlow += a[t];
	minCost += d[t] * a[t];
	for (long long int i = t; i != s; i = edges[p[i]].from)
	{
		edges[p[i]].flow += a[t];
		edges[p[i] ^ 1].flow -= a[t];
	}
	return true;
}


void MCMF()
{
	while (bellmanford(s, t))
		continue;
	return;
}

int main()
{
	long long int T ,N ,M;
	long long int i ,j ,eax;
	for(cin >> T;T--;) {
        init();
        cin >> N >> M;
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) {
            cin >> eax;
            if(eax != 0) addedge(i, 100 + j, 1, eax);
        }
        for(i = 0;i < N;i++) addedge(src, i, 1, 0);
        for(j = 0;j < M;j++) {
            cin >> eax;
            addedge(100 + j, dest, eax, 0);
        }
        MCMF();
        cout << (maxFlow == N ? minCost : -1) << endl;
	}
}
/*
2
3 3
1 2 3
6 5 4
7 8 9
3 3 3
1 1
0
1
*/
