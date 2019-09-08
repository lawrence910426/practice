#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define N 10000000
int sieve[N];
vector<int> prime;

bool is_smith(long long int a) {
	if(a < N && a == sieve[a]) return false;
	
	int digit_sum = 0 ,factor_sum = 0 ,i ,a_copy = a ,square;
	for(long long int tmp = a;tmp != 0;tmp /= 10) digit_sum += tmp % 10;
	while(a > 1) {
		if(a < N) {
			for(int tmp = sieve[a];tmp != 0;tmp /= 10) factor_sum += tmp % 10;
			a /= sieve[a];
		} else {
			square = sqrt(a) + 1;
			for(i = 2;i < square;i++)
				if(a % i == 0) {
					for(int tmp = i;tmp != 0;tmp /= 10) factor_sum += tmp % 10;
					a /= i;
					break;
				}
			if(i == square && a == a_copy) return false;
			if(i == square) {
				for(int tmp = a;tmp != 0;tmp /= 10) factor_sum += tmp % 10;
				a = 1;	
			}
		}
	}
		
	return digit_sum == factor_sum;
}

int main() {
	long long int T ,n;
	int i ,j;
	
	for(i = 0;i != N;i++) sieve[i] = i;
	for(i = 2;i != N;i++)
	{
		if(sieve[i] == i) prime.push_back(i);
		for(j = 0;j < prime.size();j++) {
			if(prime[j] * i >= N) break;
			sieve[prime[j] * i] = prime[j];
			if(i % prime[j] == 0) break;
		}
	}
	
	for(cin >> T;T--;) {
		for(cin >> n ,n += 1;!is_smith(n);n++) ; //printf("on:%d\n" ,n);
		cout << n << endl;
	}
}

/*
5
4937774
123456789
12345678
87654321
98765432
*/


/*
4937775
123456791
923456792
323456801
923126791
*/
