#include <iostream>
#include <memory.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define N 1000
int data[N] ,diff[N] ,sum[N];

using namespace std;
int main(int argc, char** argv) {
	int n ,q ,l ,r ,k ,x;		int i;
	bool init;				
	while(cin >> n >> q) {
		memset(data ,0 ,sizeof(data));
		memset(diff ,0 ,sizeof(diff));
		memset(sum ,0 ,sizeof(sum));
		init = false;
		
		for(i = 0;i != n;i++) cin >> data[i];
		for(i = 0;i != n - 1;i++) diff[i + 1] = data[i + 1] - data[i];
		for(i = 0;i != q;i++) {
			cin >> k >> l >> r;
			switch(k) {
				case 1:
					cin >> x;
					if(l == 0) data[0] += x;
					else diff[l] += x;
					diff[r + 1] -= x;	
					break;
				case 2:
					if(!init) {
						for(i = 0;i != n;i++) data[i + 1] = data[i] + diff[i + 1];		
						for(i = 0;i != n;i++) cout << data[i] << " ";		cout << endl;
						sum[0] = data[0];
						for(i = 1;i != n;i++) 
							sum[i] = sum[i - 1] + data[i];
						init = true;	
					} 
					cout << sum[r] - sum[l - 1] << endl;		
					break;	
			}
		}
	}
	return 0;
}
