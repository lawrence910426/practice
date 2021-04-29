#include <iostream>
#include <vector>

using namespace std;

const int INF = (1LL << 31) - 1;
typedef vector<pair<int, bool> > column;
typedef vector<column> storage;
int ans = INF;
bool dfs(int N, int M, storage& maps, int x, int y, int sum, bool ignore) {
	int d[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
	if(x < 0 || N <= x || y < 0 || M <= y) return true;
	if(maps[x][y].first == 0 || maps[x][y].second) return true;
	sum += maps[x][y].first;
	maps[x][y].second = true;
	ignore |= maps[x][y].first == -1;
	
	bool leaf = true;	
	for(int i = 0;i < 4;i++) leaf &= dfs(N, M, maps, x + d[0][i], y + d[1][i], sum, ignore);
	if(leaf && !ignore) ans = min(ans, sum);
	return false;
}

int main() {
	int N, M, x, y;
	int i, j;
	cin >> N >> M >> y >> x;
	storage maps = storage(N, column(M, {0, false}));
	for(int i = 0;i < N;i++) for(int j = 0;j < M;j++) cin >> maps[i][j].first;
	dfs(N, M, maps, x, y, 0, false);
	cout << ans << endl;
}
