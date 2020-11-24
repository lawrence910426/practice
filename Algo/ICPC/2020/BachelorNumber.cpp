#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define long long unsigned long long

long long P(long long a, long long b) {
	if(a < 0 || b < 0 || (a - b) < 0) return 0;
	long long ans = 1;
	for(long long i = a - b + 1;i <= a;i++) ans = ans * i;
	return ans;
}

/* The amount of bachelor numbers which is not greater than `N` under a speific system */
long long F(long long N, long long system) {
	N += 1;
	long long temp = N, digit = 0;
	for(long long i = N;i > 0;i /= system) digit += 1;
	vector<bool> used = vector<bool>(digit, false);
	vector<int> numbers = vector<int>(digit, 0);
	for(int i = 0;i < digit;i++) {
		numbers[digit - 1 - i] = temp % system;
		temp /= system;
	}
	
	long long ans = 1;
	for(int i = 1;i < digit && i <= system;i++) ans += P(system, i) - P(system - 1, i - 1);
	//printf("Smaller digit ans: %lld\n" ,ans);
	for(int i = 0;i < digit;i++) {
		for(int j = 0;j < numbers[i];j++) {
			if(j == 0 && i == 0) continue;
			if(used[j]) continue;
			ans += P(system - 1 - i, digit - 1 - i);
		}
		if(used[numbers[i]]) break;
		else used[numbers[i]] = true;
	}
	printf("%lld %lld %lld\n", N - 1, system, ans);
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
		const char* format = (vtype == 'd' ? "%lld" : "%llx");
		if(qtype == 0) {
			long long l, r, ans;
			scanf(format, &l);
			scanf(format, &r);
			ans = F(r, system) - F(l - 1, system);
			printf(format, ans);
		} else {
			long long l = 0, r = 1LL << 62, p, mid;
			scanf(format, &p);
			while(l != r - 1) {
				mid = (l + r) / 2;
				if(F(mid, system) >= p) r = mid;
				else l = mid;
			}
			if(l == (1LL << 62) - 1) printf("-");
			else printf(format, l + 1);
		}
		printf("\n");
	}	
}

void UnitTest() { for(int A, B;cin >> A >> B;) cout << F(A, B) << endl; }

int main() { Solve(); }
