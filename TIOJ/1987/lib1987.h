#ifndef LIB1987_H_INCLUDED
#define LIB1987_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void multiply(int, int, long long[], long long[], long long[]);

int main()
{
	int N, M, i;
    long long *a, *b, *ans;
    scanf("%d%d", &N, &M);
    a = (long long*)malloc(sizeof(long long) * (N + 1));
    b = (long long*)malloc(sizeof(long long) * (M + 1));
    ans = (long long*)malloc(sizeof(long long) * (N + M + 1));
    for (i = 0; i <= N; i++) scanf("%lld", a + i);
    for (i = 0; i <= M; i++) scanf("%lld", b + i);
    multiply(N, M, a, b, ans);
	for (i = 0; i <= N + M; i++) printf("%lld%c", ans[i], " \n"[i == N + M]);
}

#endif
