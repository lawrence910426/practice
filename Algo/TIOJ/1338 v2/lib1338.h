#ifndef LIB1338_H_INCLUDED
#define LIB1338_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void init(int N, long long C[]);
int query(int L, int R);

long long *C;

int main()
{
    int N, Q, a, b, i;
    scanf("%d", &N);
    if (N <= 0) puts("Invalid N");
    C = (long long*)malloc(N * sizeof(long long));
    for (i = 0; i < N; i++) scanf("%lld", C + i);
    init(N, C);
    scanf("%d", &Q);
    if (N <= 0) puts("Invalid Q");
    while (Q--) {
        scanf("%d%d", &a, &b);
        if (a >= b || a < 0 || b > N) {
            puts("Invalid query");
            break;
        }
        printf("%d\n", query(a, b));
    }
    exit(0);
}

#endif // LIB1338_H_INCLUDED


