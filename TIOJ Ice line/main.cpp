#include <iostream>
#include <memory.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define N 2048

int data[N][N] ,old[N][N];

void build(int until) {
	memset(data ,0 ,sizeof(data));
	data[0][0] = old[0][0] = 0 ,data[1][0] = old[1][0] = 1 ,data[1][1] = old[1][1] = 2 ,data[0][1] = old[0][1] = 3;
	
	
	int level ,i ,j;
	for(level = 2;level <= until;level++) {
		int len = (1 << (level - 1));
		for(i = 0;i < len;i++) for(j = 0;j < len;j++) {
			data[j][i] = old[i][j];
			data[i + len][j] = old[i][j] + len * len;
			data[i + len][j + len] = old[i][j] + len * len * 2;
			data[len - 1 - j][len + len - 1 - i] = old[i][j] + len * len * 3;
			
		}
		for(i = 0;i < len * 2;i++) for(j = 0;j < len * 2;j++) old[i][j] = data[i][j];
		
		/*cout << endl << len << endl;
		for(i = 0;i < len * 2 && i < 10;i++) {
			for(j = 0;j < len * 2 && j < 10;j++) cout << data[i][j] << "\t";
			cout << endl;
		}*/
	}
}

int main() {
	ios::sync_with_stdio(0) ,cout.tie(0);
	
	int i ,j ,n;
	while(cin >> n) {
		build(n);
		for(i = 0;i < (1 << n);cout << "\n" ,i++)	for(j = 0;j < (1 << n);j++)	
			cout << data[i][j] << " ";
		
		
	}
}
