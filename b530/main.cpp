#include <iostream>
#include <bitset>
#include <memory.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

#define N 4000

long long C[N][N];
bitset<N> A[N] ,B[N];
int main(int argc, char** argv) {
	register int n ,i ,j ,tmp;
	bool fail = false;
	ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
	while(cin >> n)
	{
		fail = false;
		memset(A ,0 ,sizeof(A));
		memset(B ,0 ,sizeof(B));
		memset(C ,0 ,sizeof(C));
		for(i = 0;i != n;i++) for(j = 0;j != n;j++)
			cin >> tmp ,A[i][j] = (tmp == 1);
		for(i = 0;i != n;i++) for(j = 0;j != n;j++) 
			cin >> tmp ,B[j][i] = (tmp == 1);
		for(i = 0;i != n;i++) for(j = 0;j != n;j++) 
			cin >> C[i][j];
		
		for(i = 0;i != n;i++) for(j = 0;j != n;j++)
			if((A[i] & B[j]).count() != C[i][j])
			{
				fail = true;
				break;
			}
				
		
		if(fail) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
}
