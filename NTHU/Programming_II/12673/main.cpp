#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 5e3 + 50, MAX_VAL = 3;

class zkw {
public:
	int leaf;
	vector<int> tag, val[MAX_VAL];
	zkw(int N) {
		for(leaf = 1;leaf < N + 2;leaf <<= 1);
		tag = vector<int>(N * 4, 0);
		for(int i = 0;i < MAX_VAL;i++) val[i] = vector<int>(N * 4, 0);
		for(int i = leaf + 1;i < leaf + 1 + N;i++) val[0][i] = 1;
		for(int i = leaf - 1;i > 0;i--) val[0][i] = val[0][i * 2] + val[0][i * 2 + 1];
	}
	void pull_up(int x) {
		for(int i = 0;i < MAX_VAL;i++) val[i][x] = 0;
		if(leaf <= x) {
			if(tag[x] < MAX_VAL) val[tag[x]][x] = 1;
		} else {
			for(int i = 0;i < MAX_VAL;i++) if(i + tag[x] < MAX_VAL) val[i + tag[x]][x] += val[i][x * 2] + val[i][x * 2 + 1];
		}
	}
	void modify(int l, int r, int delta) {
		for(l += leaf, r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
			if(l % 2 == 0) tag[l ^ 1] += delta;
			if(r % 2 == 1) tag[r ^ 1] += delta;
			pull_up(l ^ 1); 
			pull_up(r ^ 1);
		}
		for(pull_up(r);l > 0;l >>= 1) pull_up(l);
	}
	int query(int l, int r, int value) {
		int ans = 0;
		for(l += leaf, r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
			if(l % 2 == 0) ans += val[value][l ^ 1];
			if(r % 2 == 1) ans += val[value][r ^ 1];
		}
		return ans;
	}
} seg(1);

vector<pair<int, int> > interval(MAXN, {0, 0});

int query(int i, int j) {
	/* i < j */
	if(interval[j].second < interval[i].second) {
		cout << "A" << endl;
		return seg.query(interval[i].first, interval[j].first, 1) + 
			seg.query(interval[j].first, interval[j].second, 2) + 
			seg.query(interval[j].second, interval[i].second, 1);
	} else if(interval[j].first < interval[i].second) {
		cout << "B" << endl;
		return seg.query(interval[i].first, interval[j].first, 1) + 
			seg.query(interval[j].first, interval[i].second, 2) + 
			seg.query(interval[i].second, interval[j].second, 1);
	} else {
		cout << "C" << endl;
		return seg.query(interval[i].first, interval[i].second, 1) + 
			seg.query(interval[j].first, interval[j].second, 1);
	}
}

int main() {
	int T, N, Q, maxi, amount;
	int i, j;
	for(cin >> T;T--;) {
		cin >> N >> Q;
		for(i = 0;i < Q;i++) cin >> interval[i].first >> interval[i].second;
		for(i = 0;i < Q;i++) interval[i].first -= 1;
		sort(interval.begin(), interval.begin() + Q);
		cout << "---------------" << endl;
		for(i = 0;i < Q;i++) cout << interval[i].first << " " << interval[i].second << endl;
		cout << "---------------" << endl;
		
		seg = zkw(N);
		for(i = 0;i < Q;i++) seg.modify(interval[i].first, interval[i].second, 1);	
		amount = N - seg.query(0, N, 0);

		maxi = -1;
		for(i = 0;i < Q;i++) for(j = i + 1;j < Q;j++) {
			int temp = query(i, j);
			maxi = max(maxi, amount - temp);
			cout << i << " " << j << " " << temp << " " << amount - temp << endl;
		}
		cout << maxi << endl;
	}
}
