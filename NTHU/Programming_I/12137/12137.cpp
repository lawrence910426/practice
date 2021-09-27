#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;
	vector<int> weights = vector<int>(N);
	for(int i = 0;i < N;i++) cin >> weights[i];
	int ans = 0;
	for(int i = 0;i < (1 << N);i++) {
		int sum = 0;
		for(int j = 0;j < N;j++) if(i & (1 << j)) sum += weights[j];
		ans += (sum == K ? 1 : 0);
	}
	cout << ans << endl;
}
