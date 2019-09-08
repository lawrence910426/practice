#include <iostream>

#define N 10000
struct b {
	int value;	
}bit[N];			//bit[i] = sum[i] - sum[i - lowbit(i) + 1]

int data[N] ,sum[N];

#define lowbit(x) (x & -x)
#define region(l ,r) (sum[r + 1] - sum[l])			//region = summation of [l ,r]

int main(int argc, char** argv) {
	int n;			int i;
	
	sum[0] = 0;
	for(i = 1;i != n;i++) sum[i] = sum[i - 1] + data[i - 1];
	
}


//2 1 3 4 5
//0 2 3 6 10 15
