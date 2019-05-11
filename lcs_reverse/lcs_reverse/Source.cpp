#include <iostream>
#include <unordered_map>
#include <string>
#include <memory.h>
#include <algorithm>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int d[2][3] = { { -1 ,-1 ,0 } ,{ -1 ,0 ,-1 } };
struct item {
	int value;
	bool able[3];
}dp[50][50];

string src[2];
vector<string> ans;

#define maxi(a ,b ,c) (max(a ,max(b ,c)))

void dfs(int x, int y, string str) {
	if (x == 0 || y == 0)
	{
		reverse(str.begin(), str.end());
		ans.push_back(str);
	}

	for (int i = 0; i != 3; i++) {
		if (dp[x][y].able[i]) {
			if (i == 0) {
				dfs(x + d[0][i], y + d[1][i], str + src[0][x - 1]);
			}
			else {
				dfs(x + d[0][i], y + d[1][i], str);
			}
		}
	}
}

int main() {
	int t, i, j, k, counter = 0, tmp[3];
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for (cin >> t; t--;) {
		cin >> src[0] >> src[1];
		memset(dp, 0, sizeof(dp));
		for (i = 0; i != src[0].length(); i++) {
			for (j = 0; j != src[1].length(); j++) {
				if (src[0][i] == src[1][j]) tmp[0] = dp[i][j].value + 1;
				else tmp[0] = -1;
				tmp[1] = dp[i][j + 1].value, tmp[2] = dp[i + 1][j].value;

				dp[i + 1][j + 1].value = maxi(tmp[0], tmp[1], tmp[2]);
				for (k = 0; k != 3; k++)
					if (dp[i + 1][j + 1].value == tmp[k])
						dp[i + 1][j + 1].able[k] = true;
			}
		}

		ans.clear();
		dfs(src[0].length(), src[1].length(), "");

		cout << "Case #" << ++counter << ":" << " " << ans.size() << endl;

		sort(ans.begin(), ans.end());
		for (vector<string>::iterator it = ans.begin(); it != ans.end(); it++)
			cout << *it << endl;
	}
}