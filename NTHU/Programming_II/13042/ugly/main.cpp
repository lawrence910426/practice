#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 1e5 + 50;
vector<long long> raw = vector<long long>(MAXN, 0, require = vector<long long>(MAXN, 0);

int main() {
	int N;
	long long X, A, B, M;
	cin >> N >> X >> A >> B >> M;
	int i;
	
	for(i = 0;i < N;i++) cin >> raw[i];
	sort(skill.begin(), skill.end());


	require[0] = 0;
	for(i = 1;i < N;i++) require[i] = require[i - 1] + (require[i] - require[i - 1]) * (long long)i;
	
	long long ans = 0, temp, mini;
	for(i = 0;i <= N && M >= 0;i++) {
		auto it = lower_bound(require.begin(), require.end(), M);
		if(it != require.end()) {
			temp = A * (long long)i;
			mini = (M - *it) / (it - require.begin() + 1) + raw[it - require.begin()];
			temp += mini * B;
			ans = max(ans, temp);
		}
		M -= X - raw[N - i - 1];
	}
	cout << ans << endl;
}
