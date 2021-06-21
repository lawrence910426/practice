#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	int T, N, Q;
	string line;
	for(cin >> T;T--;) {
		cin >> N >> Q;
		getline(cin, line);
		vector<long long> ans = vector<long long>(N);
		while(Q--) {
			getline(cin, line);
			stringstream ss = stringstream(line);
			int row, val;
			ss >> row;
			while(ss >> val) ans[row] += val;
		}
		long long sum = 0, base = 1;
		for(int i = N - 1;i >= 0;i--) {
			sum += ans[i] * base;
			base *= 10;
		}
		cout << sum << endl;
	}
}
