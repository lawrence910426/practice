#include <iostream>
#include <memory.h>
#define N 40
#define sum(N) (N * (N + 1) / 2)
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
long long int dp[sum(N)];
using namespace std;
int main(int argc, char** argv) {
	int n;		int i ,j;
	while(cin >> n)
	{
		if(sum(n) % 2 == 1)
		{
			cout << "0" << endl;
			continue;	
		}
		
		memset(dp ,0 ,sizeof(dp));
		for(i = 1;i <= n;i++)
		{
			for(j = sum(n);j != i;j--)
			{
				if(dp[j - i] != 0) dp[j] += dp[j - i];
			}	
			dp[i] += 1;
		}
		
		cout << dp[sum(n) / 2] / 2 << endl;
	}
	return 0;
}
