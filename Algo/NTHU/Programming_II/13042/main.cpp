#include <iostream>
#include <vector>
#include <algorithm>

// #define debug
using namespace std;

vector<long long> raw, req;
vector<int> sorted;

int main() {
	int N;
	long long X, A, B, M;
	
	int i;
	cin >> N >> X >> A >> B >> M;
	req = raw = vector<long long>(N, 0);

	for(i = 0;i < N;i++) cin >> raw[i];
	for(i = 0;i < N;i++) sorted.push_back(i);
	sort(
		sorted.begin(), 
		sorted.end(), 
		[&](int a, int b) { return raw[a] < raw[b]; }
	);
#ifdef debug
	for(i = 0;i < N;i++) cout << raw[sorted[i]] << ' ';
	cout << endl;
#endif
	req[0] = 0;
	for(i = 1;i < N;i++) req[i] = req[i - 1] + (raw[sorted[i]] - raw[sorted[i - 1]]) * (long long)i;

#ifdef debug
	for(i = 0;i < N;i++) cout << req[i] << " ";
	cout << endl;
#endif

	long long full, temp, mini, remain = M, ans = 0;
	long long _full, _mini;

	for(full = 0;remain >= 0 && full < N;full += 1) {
		auto it = lower_bound(req.begin(), req.end() - full, remain);
		if(it == req.end() - full || remain < *it) it = prev(it);
		mini = raw[sorted[it - req.begin()]] + (remain - *it) / (it - req.begin() + 1);
#ifdef debug
		cout << raw[sorted[it - req.begin()]] << " " << (remain - *it) / (it - req.begin() + 1) << " " << mini << " " << remain << " " << *it << endl;
#endif
		mini = min(mini, X);
		temp = full * A + mini * B;
		if(temp > ans) {
			_full = full;
			_mini = mini;
			ans = temp;
		}
		remain -= X - raw[sorted[N - full - 1]];
	}
	
	cout << ans << endl;
	for(i = 0;i < N - _full;i++) cout << _mini << " ";
	for(i = N - _full;i < N;i++) cout << X << " ";
	cout << endl;
}
