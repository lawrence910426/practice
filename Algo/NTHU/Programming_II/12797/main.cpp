#include <iostream>
#include <cmath>
#include <memory.h>

using namespace std;

const int MAXN = 1e5 + 50;
long long raw[MAXN], prefix[MAXN], ans;

long long intersect(long long l, long long r, long long L, long long R) {
	if(r <= L) return 0;
	if(R <= l) return 0;
	if(l > L) { swap(l, L); swap(r, R); }
	if(r < R) return r - L;
	else return R - L; 
}

int main() {
	int T;
	long long A, B, C, D, ans;
	for(cin >> T;T--;) {
		cin >> A >> B >> C >> D;
		// [A, B] intersect [x - C, x - B]
		memset(raw, 0, sizeof(raw));
		for(long long x = A + B;x <= B + C;x += 1) raw[x] = intersect(A, B + 1, x - C, x - B + 1);
		memset(prefix, 0, sizeof(prefix));
		prefix[A + B] = 0;
		for(int x = A + B;x <= MAXN;x++) prefix[x + 1] = prefix[x] + raw[x];
		ans = 0;
		for(int x = C;x <= D;x++) if(x < B + C) ans += prefix[B + C + 1] - prefix[x + 1];
		cout << ans << endl;
	}
}
