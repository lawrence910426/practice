#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int> > seg;
vector<int> stat[3], prestat[3], diffsum, sum;

int query(int i, int j) {
	if(seg[i].first > seg[j].first) swap(i, j);
	if(seg[j].second < seg[i].second) {
		return 
			(prestat[2][seg[j].second] - prestat[2][seg[j].first]) + 
			(prestat[1][seg[i].second] - prestat[1][seg[i].first])
		;
	} else if(seg[i].second < seg[j].first) {
		return 
			(prestat[1][seg[j].second] - prestat[1][seg[j].first]) + 
			(prestat[1][seg[i].second] - prestat[1][seg[i].first])
		;	
	} else {
		return
			(prestat[1][seg[j].second] - prestat[1][seg[i].first]) +
			(prestat[2][seg[i].second] - prestat[2][seg[j].first])
		;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T, N, Q, maxi, amount;
	int i, j;
	for(cin >> T;T--;) {
		cin >> N >> Q;
		
		seg = vector<pair<int, int> >(Q, {0, 0});
		for(i = 0;i < 3;i++) stat[i] = prestat[i] = vector<int>(N + 1, 0);
		diffsum = sum = vector<int>(N + 1, 0);

		for(i = 0;i < Q;i++) {
			cin >> seg[i].first >> seg[i].second;
			seg[i].first -= 1;
			diffsum[seg[i].first] += 1;
			diffsum[seg[i].second] -= 1;
		}
		
		sum[0] = 0 + diffsum[0];
		for(i = 1;i < N;i++) sum[i] = sum[i - 1] + diffsum[i];

		for(i = 0;i < N;i++) if(sum[i] < 3) stat[sum[i]][i] = 1;
		for(i = 0;i < N;i++) for(j = 0;j < 3;j++) prestat[j][i + 1] = prestat[j][i] + stat[j][i];
		
		amount = N - (prestat[0][N] - prestat[0][0]);
		maxi = -1;
		for(i = 0;i < Q;i++) for(j = i + 1;j < Q;j++) maxi = max(maxi, amount - query(i, j));
		cout << maxi << '\n';
	}
}
