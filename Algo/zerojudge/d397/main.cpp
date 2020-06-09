#include <iostream>
#include <memory.h>
#include <cmath>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int coin[11] = {10000,5000, 2000,1000, 500,200, 100, 50, 20, 10, 5};
long long int dp[50000];

int fix(double d)
{
	return (int)round(d * 100);
}

int main() {
	memset(dp ,0 ,sizeof(dp));
	for(int i = 10;i != -1;i--)
	{
		dp[coin[i]] += 1;
		for(int j = 0;j != 30005;j++)
			if(dp[j] != 0) dp[j + coin[i]] += dp[j];
	}

		
	double eax; int ebx;
	while(cin >> eax ,ebx = fix(eax), ebx)
		printf("%6.2f" ,eax) ,printf("%17lld\n" ,dp[ebx]);
}
