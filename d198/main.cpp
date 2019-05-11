#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
bool data[1000][1000];
long long count[1000][1000];
#define max(a ,b) (a > b ? a : b)
#define mask(x ,y) (data[x][y] ? 0 : count[x][y])
int main(int argc, char** argv) {
	int t ,W ,N ,x ,y;
	int i ,j;
	string s;
	for(cin >> t;t--;)
	{
		cin >> W >> N;
		memset(data ,0 ,sizeof(data)) ,memset(count ,0 ,sizeof(count));
		count[1][1] = 1;
		for(i = 0;i <= W;i++)
		{
			getline(cin ,s);
			stringstream ss(s);
			ss >> x;
			while(ss >> y) data[x][y] = true;
		}
		for(i = 1;i <= W;i++) for(j = 1;j <= N;j++)
		{
			if(i == 1 && j == 1) continue;
			if(!data[i][j]) 
				count[i][j] = mask(i - 1 ,j) + mask(i ,j - 1);
		}
			
		/*for(i = 0;i <= W;cout << endl ,i++) for(j = 0;j <= N;j++)
			cout << count[i][j] << " ";*/
		cout << count[W][N] << endl;
	}
}
