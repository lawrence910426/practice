#include <iostream>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int data[100][100] ,ans[15] ,d[2][4] = {{0 ,0 ,1 ,-1} ,{1 ,-1 ,0 ,0}};

int dfs(int x ,int y ,int q)
{
	int maxi = -1;
	data[x][y] = -1;
	for(int i = 0;i != 4;i++)
		if(data[x + d[0][i]][y + d[1][i]] == q)
			maxi = max(maxi ,dfs(x + d[0][i] ,y + d[0][i] ,q))s;
	return maxi + 1;
	
}

int main() {
	int i ,j ,A ,B ,N ,H;		int counter;
	while(cin >> A >> B)
	{
		for(i = 1;i <= A;i++) for(j = 1;j <= B;j++) cin >> data[i][j];
		for(i = 1;i <= A;i++) data[i][0] = data[i][B + 1] = -1;
		for(i = 1;i <= B;i++) data[0][i] = data[A + 1][i] = -1;
		for(i = 0;i != A + 10;cout << endl ,i++) for(j = 0;j != B + 10;j++) cout << data[i][j] << " ";
		
		for(counter = 1;counter != 10;counter++)
			for(i = 0;i != A + 1;i++) for(j = 0;j != B + 1;j++)
				if(data[i][j] == counter)
					ans[counter] = max(ans[counter] ,dfs(i ,j ,counter));
		
		for(cin >> N;N--;)
			cin >> H ,cout << ans[H] << endl;
	}
}
