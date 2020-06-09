#include <iostream>
#include <cstring>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int dp[3000][3000];
int main(int argc, char** argv) {
	int i ,j;
	string a ,b;
	while(cin >> a >> b)
	{
		memset(dp ,0 ,sizeof(dp));
		for(i = 0;i != a.length();i++) for(j = 0;j != b.length();j++)
			if(a[i] == b[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
			else dp[i + 1][j + 1] = max(dp[i + 1][j] ,dp[i][j + 1]);
		cout << dp[a.length()][b.length()] << endl;
	}
}
