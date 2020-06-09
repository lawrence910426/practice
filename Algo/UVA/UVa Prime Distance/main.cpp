#include <iostream>
#include <cmath>
#include <vector>
#include <memory.h>

#define ceiling(x ,y) (x % y == 0 ? x / y : x / y + 1)
#define N (1LL << 16)
using namespace std;
long long int prime_array[N] ,segment[1000005];
vector<long long int> primes ,answer;

int main() {
	long long int L ,U ,mini ,maxi;
	long long int i ,j;
	for(i = 0;i < N;i++) prime_array[i] = i;
	for(i = 2;i < N;i++) {
		if(prime_array[i] == i) primes.push_back(i);
		for(j = 0;j < primes.size();j++) {
			if(primes[j] * i >= N) break;
			prime_array[primes[j] * i] = primes[j];
			if(i % primes[j] == 0) break;
		}
	}
	//cout << primes.size() << endl;
	
	while(cin >> L >> U) {
		memset(segment ,0 ,sizeof(segment));
		for(i = 0;i < primes.size();i++) {
			for(j = ceiling(L ,primes[i]) * primes[i];j <= U;j += primes[i]) {
				if(prime_array[j] == j) continue; //dont kill the prime numbers
				segment[j - L] = -1;
			}
		}
		
		answer.clear();
		for(i = L;i <= U;i++) if(segment[i - L] == 0) answer.push_back(i);
		for(i = 0;i < answer.size();i++) cout << answer[i] << endl;
		if(answer.size() < 2) {
			printf("There are no adjacent primes.\n");
		} else {
			for(maxi = mini = i = 0;i + 1 < answer.size();i++) {
				if(answer[i + 1] - answer[i] < answer[mini + 1] - answer[mini])
					mini = i;
				if(answer[i + 1] - answer[i] > answer[maxi + 1] - answer[maxi])
					maxi = i;
			}
				
			printf("%d,%d,%d are closest, %d,%d,%d are most distant.\n" ,
				mini ,answer[mini] ,answer[mini + 1] ,
				maxi ,answer[maxi] ,answer[maxi + 1]);
		}
	}
}
