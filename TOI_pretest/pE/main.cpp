#include <iostream>
#include <cmath>
#include <vector>
#include <memory.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
bool p[50000];
vector<int> primes;
int i ,j ,n ,ans;

int main() {
	memset(p ,0 ,sizeof(p));
	primes.push_back(2) ,primes.push_back(3);
	
	for(i = 4;i != pow(2 ,15) + 5;i++)
	{
		for(j = 0;j != primes.size();j++)
			if(i % primes[j] == 0) break;
		if(j == primes.size()) primes.push_back(i);
	}
		
	for(i = 0;i != primes.size();i++) p[primes[i]] = true;
	
	while(cin >> n ,n)
	{
		ans = 0;
		for(i = 0;i != primes.size();i++)
			if(primes[i] * 2 > n) break;
			else if(p[n - primes[i]]) ans += 1;
		cout << ans << endl;
	}
}
