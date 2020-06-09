#include <cstdio>
#include <memory.h>
#include <algorithm>

using namespace std;

#define q_size 2500005
#define getlen(eax) (log2(eax.end - eax.start))
#define _CRT_SECURE_NO_WARNING

struct query {
	int start, end;
	bool operator< (query eax)&{	return (end - start) < (eax.end - eax.start);	}
}qs[q_size];

int n, q , dp[7500005] ,dp_len;

int main()
{
	int i, j;
	while (memset(qs ,0 ,sizeof(qs)) ,memset(dp ,0 ,sizeof(dp))
		,scanf("%d %d", &q, &n) != EOF)
	{
		for (i = 0; i != q; i++) scanf("%d %d" ,&qs[i].start ,&qs[i].end);
		for (i = 0; i != n; i++) scanf("%d", &(dp[i]));
		for (i = 0, dp_len = 0, sort(qs, qs + q_size)
			; i != q; i++)
		{
			while (dp_len != getlen(qs[i]))
				for (j = 0, dp_len += 1
					; j != n - (1 << dp_len) + 1; j++)
					dp[j] = max(dp[j], dp[j + (1 << dp_len - 1) + 1]);
			printf("%d", max(dp[qs[i].start], dp[qs[i].end - (1 << dp_len) + 1]));
		}
			
	}
}