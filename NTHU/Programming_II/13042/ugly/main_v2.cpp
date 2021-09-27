#include <iostream>
#include <vector>

using namespace std;
const int MAXN = 1e5 + 50;

auto raw = vector<long long>(MAXN, 0), require = vector<long long>(MAXN, 0), optimal = vector<long long>(MAXN, 0);
auto skills = vector<pair<long long, int> >(MAXN, {0, 0}); 

int main() {
	int N;
	long long X, A, B, M;
	cin >> N >> X >> A >> B >> M;
	int i;
	for(i = 0;i < N;i++) cin >> raw[i];

	for(i = 0;i < N;i++) skills[i] = {raw[i], i};
	sort(skills.begin(), skills.end());
	require[0] = 0;
	for(i = 1;i < N;i++) require[i] = (require[i] - require[i - 1]) * (long long)(i);

	long long ans = 0, temp, mini, remaining = M;
	int best_fulls = -1;
	for(i = 0;remaining >= 0 && i < N;i++) {
		auto it = lower_bound(require.begin(), require.end() - i, remaining);
		if(it == require.end() - i) it = prev(it);
		mini = (remaining - *it) / (it - require.begin() + 1) + skills[it - require.begin()];
		mini = min(mini, X);
		temp = A * (long long)i + B * mini;
		if(temp > ans) {
			ans = temp;
			best_fulls = i;
		}
		remaining -= X - skills[N - i - 1].first;
	}

	cout << ans << endl;
	
	remaining = M;
	for(i = 0;i < best_fulls;i++) remaining -= X - skills[N - i - 1].first;

	auto it = lower_bound(require.begin(), require.end() - i, remaining);
	if(it == require.end() - i) it = prev(it);
	mini = (remaining - *it) / (it - require.begin() + 1) + skills[it - require.begin()];
	mini = min(mini, X);
	for(i = N - 1;i > N - 1 - best_fulls;i--) raw[skills[i].second] = X;
	for(;i >= 0;i--) raw[skills[i].second] = mini;	
	for(i = 0;i < N;i++) cout << raw[skills[i].second] << " ";

}
