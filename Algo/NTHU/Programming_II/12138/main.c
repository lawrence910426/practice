#pragma GCC optimize("Ofast")

#include <stdio.h>
#define min2(a, b) ((a) > (b) ? (b) : (a))
#define min3(a, b, c) (min2((a), min2((b), (c))))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define MAXN (1000000 + 50)

long long prefix[MAXN], raw[MAXN];

int main() {
    int N, Q, l, r, m, i, pivot;
    scanf("%d %d\n", &N, &Q);
    for(i = 0;i < N;i++) scanf("%lld", &raw[i]);
    for(prefix[0] = i = 0;i < N;i++) prefix[i + 1] = prefix[i] + raw[i];
    for(i = 0;i < N && raw[i] > 0;i++) pivot = i;
    pivot += 1;

    while(Q--) {
        scanf("%d %d %d", &l, &r, &m);
        l -= 1;
        printf("%lld\n", prefix[max(l, min3(r, l + m, pivot))] - prefix[l]);
    }
}
