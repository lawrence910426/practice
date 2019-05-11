#include <iostream>
#include <memory.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int dp[105];	//dp[weight] = value.
using namespace std;

int main() {
	int t ,i ,w ,v ,ans;
	while(cin >> t)
	{
		memset(dp ,0 ,sizeof(dp));
		while(t--)
		{
			cin >> w >> v;
			for(i = 100;i - w != -1;i--) 
				if(dp[i - w] != 0)
					dp[i] = max(dp[i] ,v + dp[i - w]);
			dp[w] = max(dp[w] ,v);
		}
		for(ans = 0 ,i = 0;i != 100;i++) ans = max(ans ,dp[i]);
		cout << ans << endl;
	}
}
