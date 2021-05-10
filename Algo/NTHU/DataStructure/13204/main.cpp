#include <iostream>
#include <vector>
#include <set>

using namespace std;

set<pair<int, int> > S;
int R, C;
int dfs(int x, int y, int len) {
	if(x == R - 1 && y == C - 1 && S.find({x, y}) != S.end()) return len;
	if(x < 0 || R <= x || y < 0 || C <= y) return 0;
	if(S.find({x, y}) == S.end()) return 0;
	S.erase({x, y});
	int temp, d[2][4] = { {0, 0, 1, -1}, {1, -1, 0, 0} };
	for(int i = 0;i < 4;i++) {
		temp = dfs(x + d[0][i], y + d[1][i], len + 1);
		if(temp != 0) return temp;
	}
	return 0;
}

int main() {
	int temp;
	cin >> R >> C;
	for(int i = 0;i < R;i++) for(int j = 0;j < C;j++) {
		cin >> temp;
		if(temp == 1) S.insert({i, j});
	}
	cout << dfs(0, 0, 1) << endl;
}
