///#pragma GCC optimize("Ofast,no-stack-protector")
#include "lib1995.h"
//#include <iostream>
//#include <stdio.h>
//#include <memory.h>
#define max(a ,b) (a > b ? a : b)
const int MAXN = 2500005;
const int MAXQ = 1000005;
using namespace std;
int sparse_table[MAXN] ,query[MAXQ][2] ,N ,Q ,finished;
bool done[MAXQ];
int layer ,i;

int main() {
    while(scanf("%d %d" ,&N ,&Q) != EOF) {
        memset(done ,0 ,sizeof(done));
        for(i = 0;i < Q;i++) scanf("%d %d" ,&query[i][0] ,&query[i][1]);
        for(i = 0;i < Q;i++) query[i][0] -= 1;
        for(i = 0;i < N;i++) scanf("%d" ,&sparse_table[i]);
        for(finished = layer = 0;finished < Q;layer++) {
            for(i = 0;i < Q;i++)
                if(__lg(query[i][1] - query[i][0]) == layer && !done[i]) {
                    query[i][0] = max(sparse_table[query[i][0]] ,sparse_table[query[i][1] - (1 << layer)]);
                    done[i] = true;
                    finished += 1;
                }
            for(i = 0;i + (1 << layer) < N;i++) sparse_table[i] = max(sparse_table[i] ,sparse_table[i + (1 << layer)]);
        }
        for(i = 0;i < Q;i++) printf("%d\n" ,query[i][0]);
    }
    return 0;
}
