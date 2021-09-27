#include <iostream>
#include <vector>

const int MAXN = 5e3 + 50;
vector<int> amount, stat[3], prefix_stat[3], prefix_amount;
vector<pair<int, int> > seg;

int main() {
	int T, N, Q;
	int i;
	for(cin >> T;T--;) {
		cin >> N >> Q;
		
		for(i = 0;i < 3;i++) stat[i] = prefix_stat[i] = vector<int>(N + 1, 0);
		seg = vector<pair<int, int> >(Q, {0, 0});
		amount = vector<int>(N, 0);
		prefix_amount = vector<int>(N + 1, 0);

		for(i = 0;i < N;i++) {
			cin >> seg[i].first >> seg[i].second;
			seg[i].first -= 1;
			prefix_amount[seg[i].first] += 1;
			prefix_amount[seg[i].second] -= 1;
		}
		
		amount[0] = 0 + prefix_amount[0];
		for(i = 1;i < N;i++) amount[i] = amount[i - 1] + prefix_amount[i];
		
		for(i = 0;i < N;i++) if(amount[i] < 3) stat[amount[i]] = 1;
	
	}
}
