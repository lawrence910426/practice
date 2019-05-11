#include <iostream>
#include <memory.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
#define N 1000005
int diff[N] ,data[N];

int main(int argc, char** argv) {
	int n ,T ,l ,r ,ans ,L ,R;
	int i;
	while(cin >> n >> T) {
		memset(diff ,0 ,sizeof(diff));
		memset(data ,0 ,sizeof(data));
		for(i = 0;i < n;i++) {
			cin >> l >> r;
			diff[l] += 1 ,diff[r + 1] -= 1;
			if(i == 0) L = l ,R = r;
		}
		
		data[0] = 0;
		for(i = 1;i <= T;i++) 
			data[i] = data[i - 1] + diff[i];
		
		//for(i = 0;i <= T;i++) cout << i << " " << diff[i] << " " << data[i] << endl;
		
		ans = 0;
		for(i = L;i <= R;i++)
			if(data[i] > n / 2) ans += 1;
		cout << ans << endl;
	} 
	return 0;
}

/*
1 100
2 100

3 10
2 8
1 7
9 10

3 10
9 10
2 8
1 7
*/
