#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<pair<int, int> > > dist;
vector<double> cent;

void merge(pair<int, int>& T, pair<int, int> A, pair<int, int> B) {
	if(A.first == 0 || B.first == 0) return;
	pair<int, int> alt = {A.first + B.first, A.second};
	if(T.first == 0 || T > alt) T = alt;
}

int main() {
	int N, i, j, k;
	cin >> N;
	dist = vector<vector<pair<int, int> > >(N, vector<pair<int, int> >(N, {0, 0}));
	cent = vector<double>(N, 0);
	for(i = 0;i < N;i++) for(j = 0;j < N;j++) cin >> dist[i][j].first;
	for(i = 0;i < N;i++) for(j = 0;j < N;j++) dist[i][j].second = j;
	for(k = 0;k < N;k++) for(i = 0;i < N;i++) for(j = 0;j < N;j++) merge(dist[i][j], dist[i][k], dist[k][j]);
	for(i = 0;i < N;i++) for(j = 0;j < N;j++) if(i != j && dist[j][i].first != 0) cent[i] += 1.0 / dist[j][i].first;
	for(i = 0;i < N;i++) for(j = 0;j < N;j++) if(i != j && dist[i][j].first != 0) {
		cout << "Path(" << i << "," << j << ")" << ":";
		for(k = i;k != j;k = dist[k][j].second) cout << k << "->";
		cout << j << endl << "Difficulty:" << dist[i][j].first << endl;
	}
	for(i = 0;i < N;i++) cout << "Centrality(" << i << "):" << fixed << setprecision(3) << cent[i] << endl;	
}
