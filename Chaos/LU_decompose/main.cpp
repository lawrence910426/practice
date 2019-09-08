#include <iostream>
#include <memory.h>
#define N 3
using namespace std;
int main()
{
    float A[N][N] ,B[N] ,Y[N] ,X[N] ,L[N][N] ,U[N][N] ,rate ,sum;
    int i ,j ,k;
    
    cout << "Input your A:(" << N << "," << N << ")" << endl;
    for(i = 0;i != N;i++) for(j = 0;j != N;j++) cin >> A[i][j];
    
    memset(L ,0 ,sizeof(L)); memset(X ,0 ,sizeof(X)); memset(Y ,0 ,sizeof(Y));
    for(i = 0;i != N;i++) L[i][i] = 1;
    for(i = 0;i < N;i++) for(j = i + 1;j < N;j++) {
        rate = A[j][i] / A[i][i];
        L[j][i] = rate;
        for(k = 0;k < N;k++) A[j][k] -= rate * A[i][k];
    }
	memcpy(U ,A ,sizeof(A));
	
	cout << "--------" << endl;
	for(i = 0;i != N;i++ ,cout << endl) for(j = 0;j != N;j++) cout << L[i][j] << " ";
	cout << "--------" << endl;
	for(i = 0;i != N;i++ ,cout << endl) for(j = 0;j != N;j++) cout << U[i][j] << " ";
	
	cout << "Input your B:(" << N << ")" << endl;
	for(i = 0;i != N;i++) cin >> B[i];
	
	for(i = 0;i != N;i++) {
		for(sum = 0, j = 0;j != i;j++) sum += Y[j] * L[i][j];
		Y[i] = (B[i] - sum) / L[i][i];
	}
	cout << "--------" << endl;
	for(i = 0;i != N;i++) cout << Y[i] << " ";
	
	for(i = N - 1;i >= 0;i--) {
		for(sum = 0, j = N - 1;j > i;j--) sum += X[j] * U[i][j];
		X[i] = (Y[i] - sum) / U[i][i];
	}
	cout << endl << "--------" << endl;
	for(i = 0;i != N;i++) cout << X[i] << " ";
	
}

/*
3 -1 2
6 -1 5
-9 7 3

1 3 2
*/

