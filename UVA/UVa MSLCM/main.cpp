#include <iostream>
#include <vector>
using namespace std;
#define N 20000001
int sum[N] ,primes[N];
vector<int> ps;

inline void ptable() {
	int i ,j;
	for(i = 0;i <N;i++) primes[i] = i;
	for(i = 2;i < N;i++) {
		if(primes[i] == i) ps.push_back(i);
		for(j = 0;j < ps.size();j++) {
			if(i * ps[j] > N) break;
			primes[i * ps[j]] = ps[j];
			if(i % ps[j] == 0) break;
		}
	}
}

int eqser_sum(int r ,int n) {
	int ret = r ,tmp = r;
	while(n) {
		if(n & 1) ret *= tmp;
		n >>= 1;
		tmp *= tmp;
	}
	//cout << ret << endl;
	return (ret - 1) / (r - 1);
}

inline int fsum(int x) {
	int last = primes[x], count = 0 ,ans = 1;
	while(x != 1) {
		if(primes[x] != last) {
			ans *= eqser_sum(last ,count);
			//printf("%d %d\n" ,last ,count);
			count = 0;
			last = primes[x];
		}
		x /= primes[x];
		count += 1;
	}
	ans *= eqser_sum(last ,count);
	//printf("%d %d\n" ,last ,count);
	return ans;
}

int main() {
	int i ,n;
	ptable();
	for(sum[1] = 0, i = 2;i < N;i++) sum[i] = sum[i - 1] + fsum(i);
	while(cin >> n) {
		cout << fsum(n) << endl;
	}
}


// Yep, this will TLE.
// This is what i do.
// Jiang li zhi shu biao ,ran hou dua 'x' jing shing zhi yin shu fen jeh
// Li yong fen jeh hao de zhi yin shu ,ghi suan 'x' de yin shi he
// Zai du jian biao ,jhi ke O(1) hua da wen ti.
