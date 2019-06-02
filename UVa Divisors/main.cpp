#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#define N 1000000000
#define n 32000

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int prime[n];
vector<int> prime_v;

void table() {
	int i ,j;
	for(i = 0;i < n;i++) prime[i] = i;
	for(i = 2;i < n;i++) {
		if(prime[i] == i) prime_v.push_back(i);
		for(j = 0;j < prime_v.size();j++) {
			if(i * prime_v[j] >= n) break;
			prime[i * prime_v[j]] = prime_v[j];
			if(i % prime_v[j] == 0) break;
		}
	}
}

int divisors(int value) {
	map<int ,int> p;
	int i;
	for(i = 0;i < prime_v.size() && value != 1;) {
		if(value < n) {
			while(value != 1) {
				p[prime[value]] += 1;
				value /= prime[value];
			}
		} else {
			if(value % prime_v[i] == 0) {
				value /= prime_v[i];
				p[prime_v[i]] += 1;
			} else {
				i += 1;
			}
		}
	}
	
	int ret = 1;
	for(auto iter = p.begin();iter != p.end();iter++)
		ret *= (iter->second + 1); // ,cout << iter->first << " "  << iter->second << endl;
	return ret;
}

int main(int argc, char** argv) {
	int T ,i ,l ,r ,maxi_v ,maxi ,tmp;
	table();
	ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
	for(cin >> T;T--;) {
		cin >> l >> r;
		maxi_v = maxi = -1;
		for(i = l;i <= r;i++) {
			tmp = divisors(i);
			if(maxi_v < tmp) {
				maxi_v = tmp;
				maxi = i;
			}
		}
		printf("Between %d and %d, %d has a maximum of %d divisors.\n" ,l ,r ,maxi ,maxi_v);
	}
}
