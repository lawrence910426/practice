#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
const int MAXN = 1e3 + 50;

vector<pair<int, int> > coord;
bitset<MAXN> black;

class DSU {
public:
	vector<int> par = vector<int>(MAXN, 0);
	DSU() { for(int i = 0;i < MAXN;i++) par[i] = i; }
	int query(int i) { return (i == par[i] ? i : par[i] = query(par[i])); }
	void join(int a, int b) { par[query(a)] = par[query(b)]; }
} DisjointSet;

int main() {
	int N, R;
	cin >> N >> R;
	int i, j, x, y;
	for(i = 0;i < N;i++) {
		cin >> x >> y;
		coord.push_back({x, y});
	}
	for(i = 0;i < N;i++) for(j = 0;j < N;j++) if((coord[i].first - coord[j].first) * (coord[i].first - coord[j].first) + (coord[i].second - coord[j].second) * (coord[i].second - coord[j].second) <= R * R) DisjointSet.join(i, j);
	
	black.reset();
	for(i = 0;i < N;i++) if(DisjointSet.par[i] != i) black[i] = black[DisjointSet.par[i]] = true;
	int black_holes = 0;
	for(i = 0;i < N;i++) if(black[i] && DisjointSet.par[i] == i) black_holes += 1;
	cout << N - black.count() << " " << black_holes << endl;
}
