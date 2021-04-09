#include <iostream>
#include <vector>

using namespace std;
const int INF = (1LL << 31) - 1;

int main() {
	int N, K, ans = INF;
	int i, j, a, b, value, weight;
	vector<pair<int, int> > Data;
	cin >> N >> K;
	for(i = 0;i < N;i++) {
		cin >> a >> b;
		Data.push_back({a, b});
	}
	for(i = 0;i < (1 << N);i++) {
		value = weight = 0;
		for(j = 0;j < N;j++) {
			if(i & (1 << j)) {
				value += Data[j].first;
				weight += Data[j].second;
			}
		}
		if(value >= K) ans = min(ans, weight);
	}
	cout << ans << endl;
}
