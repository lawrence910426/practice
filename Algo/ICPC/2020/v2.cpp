#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long ull;
#define MAXI 0xFEDCBA9876543210ULL

ull P(ull A, ull B) {
	if(A < 0 || B < 0 || A < B) return 0;
	ull ans = 1;
	for(ull i = A - B + 1;i <= A;i++) ans *= i;
	return ans;
}

ull F(ull N, ull system) {
	if(N == 0) return 0;

	int i = 0;
	ull digit = 0, temp;
	for(temp = N;temp > 0;temp /= system) digit += 1;
	vector<bool> used = vector<bool>(digit, false);
	vector<int> num = vector<int>(digit, 0);
	for(temp = N;temp > 0;temp /= system) num[digit - 1 - (i++)] = temp % system;

	ull ans = 1;
	for(i = 1;i < digit && i <= system;i++) ans += P(system, i) - P(system - 1, i - 1);
	for(i = 0;i < digit;i++) {
		for(int j = 0;j < num[i];j++) {
			if((i == 0 && j == 0) || used[j]) continue;
			ans += P(system - 1 - i, digit - 1 - i);
		}
		if(used[num[i]]) break;
		used[num[i]] = true;
	}
	return ans;
}

void Solve() {
	int N;
	char vtype;
	int qtype, system;
	cin >> N;
	while(N--) {
		cin >> vtype >> qtype;
		system = (vtype == 'd' ? 10 : 16);
		auto format = (vtype == 'd' ? dec : hex);
		if(qtype == 0) {
			ull l, r;
			cin >> format >> l >> format >> r;	
			r = min(r, MAXI);
			cout << format << F(r + 1, system) - F(l, system) << endl;
		} else {
			ull l = 0, r = MAXI + 1, p, mid;
			cin >> format >> p;
			while(l != r - 1) {
				mid = l + (r - l) / 2;	
				if(F(mid, system) >= p) r = mid;
				else l = mid;
			}
			if(l == MAXI) cout << "-" << endl;
			else cout << format << l << endl;
		}
	}
}

int main() { Solve(); }
