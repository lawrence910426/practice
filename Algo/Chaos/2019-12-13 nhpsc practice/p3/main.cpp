#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

int N ,K ,data[50] ,color[10];
int main() {
    int i ,j ,ptr;
    float ans ,diff ,sum;
    while(cin >> N >> K) {
        for(i = 0;i < K;i++) cin >> color[i];
        for(ptr = i = 0;i < K;i++) for(j = 0;j < color[i];j++) data[ptr++] = i;
        diff = sum = 0;
        do {
            sum += 1;
            for(i = 0;i < N - 1;i++) if(data[i] != data[i + 1]) diff += 1;
        } while(next_permutation(data ,data + N));
        ans = diff / sum;
        printf("%.3f\n" ,ans);
    }
}
