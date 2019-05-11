#include <iostream>
#include <memory.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char map[50][50];
int d[2][8] = {{0 ,0 ,1 ,-1 ,-1 ,1 ,-1 ,1 }
			  ,{1 ,-1 ,0 ,0 ,1 ,1 ,-1 ,-1}};
using namespace std;
int main() {
	int i ,j ,k;	char eax;
	
	
	{
		for(memset(map ,0 ,sizeof(map)) ,i = 1;i != 16;i++) for(j = 1;j != 31;j++)
			cin >> eax ,map[i][j] = (eax == '*' ? '*' : 0);
	
		for(i = 1;i != 16;i++) for(j = 1;j != 31;j++)
			if(map[i][j] != -1)
				for(k = 0;k != 8;k++)
					map[i][j] += (map[i + d[0][k]][j + d[1][k]] == '*' && map[i][j] != '*'
						? 1 : 0);
	
		for(i = 1;i != 16;cout << endl ,i++) for(j = 1;j != 31;j++)
			cout << (map[i][j] == '*' ? '*' :
				(map[i][j] == 0 ? '.' : (char)(map[i][j] + '0')));	
	}		
}
