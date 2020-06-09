#pragma GCC optimize("Ofast,unroll-loops")
#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
const long long MAXN = (1LL << 16);
long long n, a[50000] = {2,3,0} ,c;
long long i ,j;
bool is_prime[MAXN];
void build() {
	is_prime[2] = is_prime[3] = true;
	for (i = 4; i < MAXN; ++i) {
		n = 1;
		while (i % a[n-1] != 0) {
			n++;
			if (a[n] == 0) {
				a[n] = i;
				is_prime[i] = true;
				break;
			}
		}
	}
}
void build_fast() {
    for(i = 0;i < MAXN;i++) is_prime[i] = true;
    n = 0;
    for(i = 2;i < MAXN;i++) {
        if(is_prime[i]) a[n++] = i;
        for(j = 0;j < n;j++) {
            if(i * a[j] >= MAXN) break;
            is_prime[i * a[j]] = false;
            if(i % a[j] == 0) break;
        }
    }
}
int main() {
    build_fast();
	cin.tie(0);
	ios::sync_with_stdio(false);
    while(cin >> c) {
        if(c < MAXN) cout << (is_prime[c] ? "質數" : "非質數") << '\n';
        else {
            for(i = 0;a[i] != 0;i++) if(c % a[i] == 0) {
                cout << "非質數" << '\n';
                break;
            }
            if(a[i] == 0) cout << "質數" << '\n';
        }
	}
}
