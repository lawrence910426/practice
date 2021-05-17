#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const int MAXN = 1e2 + 5;
typedef pair<int, string> cell;
cell dist[MAXN][MAXN];
double cent[MAXN];

void merge(cell& t, cell& a, cell& b) {
	if(a.first == 0 || b.first == 0) return;
	cell alt = {a.first + b.first, a.second + b.second};
	if(t.first == 0 || t > alt) t = alt;
}

int main() {
	int N;
	cin >> N;
	for(int i = 0;i < N;i++) for(int j = 0;j < N;j++) dist[i][j].second = "->" + to_string(j);
	for(int i = 0;i < N;i++) for(int j = 0;j < N;j++) cin >> dist[i][j].first;
	for(int k = 0;k < N;k++) for(int i = 0;i < N;i++) for(int j = 0;j < N;j++) merge(dist[i][j], dist[i][k], dist[k][j]);
	for(int i = 0;i < N;i++) cent[i] = 0;
	for(int i = 0;i < N;i++) for(int j = 0;j < N;j++) if(dist[j][i].first != 0 && i != j) cent[i] += 1.0 / dist[j][i].first;
	for(int i = 0;i < N;i++) for(int j = 0;j < N;j++) if(dist[i][j].first != 0 && i != j) cout << "Path(" << i << "," << j << "):" << i << dist[i][j].second << endl << "Difficulty:" << dist[i][j].first << endl;
	for(int i = 0;i < N;i++) cout << "Centrality(" << i << "):" << fixed << setprecision(3) << cent[i] << endl;
}
