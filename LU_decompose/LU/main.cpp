#include <iostream>
#include <memory.h>
#define N 3
using namespace std;
int main()
{
    float A[N][N] ,B[N] ,L[N][N] ,U[N][N] ,rate;
    int i ,j ,k;
    for(i = 0;i != N;i++) for(j = 0;j != N;j++) cin >> A[i][j];
    for(i = 0, memset(L ,sizeof(L));i != N;i++) L[i][i] = 1;
    for(i = 0;i < N;i++) for(j = i + 1;j < N;j++) {
        rate = A[i][i] / A[j][i];
        for(k = 0;k < N;k++) A[j][k] += rate * A[i][k];
    }

    for(i = 0;i != N;cout << endl ,i++) for(j = 0;j != N;j++) cout << L[i][j] << " ";
    for(i = 0;i != N;cout << endl ,i++) for(j = 0;j != N;j++) cout << U[i][j] << " ";
}
