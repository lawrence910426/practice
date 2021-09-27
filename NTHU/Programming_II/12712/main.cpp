#include <iostream>

using namespace std;

int main() {
	int T;
	for(cin >> T;T--;) {
		__int128 x, k, n, ans = (1LL << 63) - 1;
		__int128 l, r, mid;
		long long X;
		cin >> X;
		x = X;
		
		int i;
		for(i = 0;i < 60;i++) {
			k = 1LL << i;
			l = 1;
			r = (1LL << 31) - 1;
			while(l != r - 1) {
				mid = (l + r) >> 1;
				if(mid * (mid - 3) / 2 + k * mid > x) r = mid;
				else l = mid;
			}
			if(l % 2 == 1 && l * (l - 3) / 2 + k * l == x) n = l;
			else continue;
			
			ans = min(ans, n * k);
		}
		if(ans == (1LL << 63) - 1) cout << -1 << endl;
		else cout << (long long)ans << endl;
	}
}
