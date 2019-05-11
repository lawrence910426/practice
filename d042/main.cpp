#include <iostream>
#include <memory.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
long long int dp[100][100][10];

int main(int argc, char** argv) {
	memset(dp ,0 ,sizeof(dp));
	int n ,s ,i ,j;
	dp[1][1][1] = dp[1][0][0]= 1;
 	for(i = 2;i != 67;i++)
 	{
 		dp[i][0][0] = dp[i - 1][1][1] + dp[i - 1][0][0];
 		for(j = 1;j <= i;j++)
 		{
 			dp[i][j][0] = dp[i - 1][j][0] + dp[i - 1][j + 1][1];
 			dp[i][j][1] = dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1];
		}
	}
 		
	while(cin >> n >> s ,true) 
		if(n < 0 && s < 0) break;
		else cout << dp[n][s][0] + dp[n][s][1] << endl;
	return 0; 
}
