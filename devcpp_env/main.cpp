#include <cstdio>
#include <memory.h>
#include <algorithm>

using namespace std;

#define q_size 1000005
#define getlen(eax) (__lg(eax.end - eax.start))
#define length(dp_len) ((1 << dp_len) - 1)
#define maxx(a ,b ,c) (a = max(max(b ,c) ,a))

int n, q , dp[2500005] ,dp_len ,qs[1000005][3];		//qs[i][0] = start ,qs[i][1] = end ,qs[i][2] = ans.

int main()
{
	int i, j;
	while (memset(qs ,0 ,sizeof(qs)) ,memset(dp ,0 ,sizeof(dp))
		,scanf("%d %d", &n, &q) != EOF)
	{
		for (i = 0; i != q; i++) scanf("%d %d" ,&qs[i][0] ,&qs[i][1]) ,qs[i][2] = -1 ,qs[i][0] -= 1 ,qs[i][1] -= 1;
		for (i = 0; i != n; i++) scanf("%d", &dp[i]);
		for (dp_len = 0; dp_len <= __lg(n) + 1; dp_len++)
		{
			for(i = 0; i != q; i++)
				if(qs[i][1] - qs[i][0] <= length(dp_len))
					qs[i][2] = max(qs[i][2] ,max(dp[qs[i][0]] ,dp[qs[i][1] - length(dp_len)]));
			for(i = 0; i <= n - length(dp_len); i++)
				dp[i] = max(dp[i] ,dp[i + length(dp_len)]);
		}
			
		for (i = 0; i != q; i++) printf("%d\n" ,qs[i][2]);
	}
}
