#include <iostream>
#include <queue>

#define make eax.value = q.front().value + 1 ,eax.x = q.front().x + d[0][i] ,eax.y = q.front().y + d[1][i]
#define dbg for(i = 0;i != n + 2;cout << endl ,i++) for(j = 0;j != m + 2;j++) cout << mapa[i][j];
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct pt{
	int x ,y ,value;
};
char mapa[700][700]; int d[2][4] = {{0 ,0 ,1 ,-1} ,{1 ,-1 ,0 ,0}};
int main() {
	int n ,m ,ans;		int i ,j;		pt src ,dst ,eax;	queue<pt> q;
	while(cin >> n >> m)
	{
		for(i = 1;i != n + 1;i++) for(j = 1;j != m + 1;j++) 
			if(cin >> mapa[i][j] ,mapa[i][j] == 'X') src.x = i ,src.y = j ,src.value = 1;
			else if(mapa[i][j] == 'Y') dst.x = i ,dst.y = j;
		for(i = 0;i <= max(n ,m);i++) mapa[i][0] = mapa[0][i] = mapa[n + 1][i] = mapa[i][m + 1] = '#';
		for(q = queue<pt>(), q.push(src);!q.empty();q.pop())
		{
			for(i = 0;i != 4;i++)
			switch(mapa[q.front().x + d[0][i]][q.front().y + d[1][i]])
			{
				case 'X':
					make ,q.push(eax);
					break;
				case '.':
					make ,q.push(eax);
					break;
				case 'A':
					if(q.front().value != 0) make ,q.push(eax);
					break;
				case 'B':
					if(q.front().value != 1) make ,q.push(eax);
					break;
				case 'C':
					if(q.front().value != 2) make ,q.push(eax);
					break;
				case 'Y':
					ans = q.front().value; goto exit;
					break;
			}
		}
	exit:
		cout << ans << endl;
	}
}
