#include <iostream>
#include <bitset>
#include <memory.h>

using namespace std;

#define N 16
#define min(a ,b) (a > b ? b : a)
#define max(a ,b) (a > b ? a : b)
#define adapt(i) (i == -1 ? 1LL << 31 - 1 : i)
int data[N][N];
struct t{
	int maxi ,mini;	
}tsm[N][1 << N];

int gcd(int a ,int b) {
	if(a == 0) return b;
	if(b == 0) return a;
	return gcd(b % a ,a);
}

int main() {
	int n ,maxi ,mini ,factor;			int i, j, k ,tmp;
	while (cin >> n) {
		for (i = 0; i < n; i++) for (j = i + 1; j < n; j++) {
			cin >> tmp;
			data[i][j] = data[j][i] = tmp;
		}
		memset(tsm, -1, sizeof(tsm));

		for (i = 1; i != n; i++) tsm[i][1 << i].mini = tsm[i][1 << i].maxi = data[i][0];
			

		for (i = 1; i <= 1 << n; i++) {
			if (!(i & (i - 1))) continue;
			if (i & 1) continue;
			for (j = 1; j != n; j++) {

				tmp = i - (1 << j);
				for (k = 0; k != n; k++)
				{
					if ((tmp >> k) & 1)
					{
						tsm[j][i].mini = min(tsm[k][tmp].mini + data[j][k], adapt(tsm[j][i].mini));
						tsm[j][i].maxi = max(tsm[k][tmp].maxi + data[j][k], tsm[j][i].maxi);
					}
				}
			}
		}

		mini = 1LL << 31 - 1;
		maxi = -1;
		for (i = 1; i != n; i++) {
			mini = min(mini, tsm[i][(1 << n) - 2].mini + data[i][0]);
			maxi = max(maxi, tsm[i][(1 << n) - 2].maxi + data[i][0]);
		}
		
		factor = gcd(maxi ,mini);
		
		if(mini == factor)
			printf("%d\n" ,maxi / factor);
		else
			printf("%d/%d\n" ,maxi / factor ,mini / factor);
	}
}
