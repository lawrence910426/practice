#include <iostream>

#define min(a ,b) (a > b ? b : a)
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int coins[100000];
int dp[10000000];
int main(int argc, char** argv) {
	int c ,n;			int i ,j;
	cin >> c >> n;
	for(i = 0;i != n;i++) cin >> coins[i];
	
	for(i = 0;i != n;i++) 
	{
		dp[coins[i]] = 1;
		for(j = 0;j != c;j++)
		{
			if(dp[j] != 0)
			{
				if(dp[j + coins[i]] == 0) dp[j + coins[i]] = dp[j] + 1;
				else dp[j + coins[i]] = min(dp[j] + 1 ,dp[j + coins[i]]);
			}
		}
	}
	
	/*for(i = 0;i != c + 1;i++)
		cout << i << "\t" << dp[i] << endl;*/
	cout << dp[c] << endl;
	return 0;
}
