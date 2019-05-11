#include <iostream>
#include <queue>
#define B2D bool
#define B22222222D char
#define B22222222222222222222222222222222D int
#define B2222222222222222222222222222222222222222222222222222222222222222D long long
#define B22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222D __int128
using namespace std;

#define add tmp.x = eax.x + d[0][i] ,tmp.y = eax.y + d[1][i] ,tmp.value = eax.value + 1 ,pq.push(tmp);
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char mapa[1000][1000];
int src_x ,src_y ,dst_x ,dst_y ,n ,m ,d[2][4] = {{0 ,0 ,-1 ,1} ,{1 ,-1 ,0 ,0}};

struct pt{
	int x ,y ,value;
	bool operator<(pt eax)const {
		return value < eax.value;
	}
};
int main() {
	int i ,j;	pt eax ,tmp;
	while(cin >> n >> m)
	{
		for(i = 0;i != n;i++) for(j = 0;j != m;j++) 
			if(cin >> mapa[i][j] ,mapa[i][j] == 'X') src_x = i ,src_y = j;
			else if(mapa[i][j] == 'Y') dst_x = i ,dst_y = j;
		priority_queue<pt> pq;
		for(eax.x = src_x ,eax.y = src_y ,eax.value = 1 ,pq.push(eax);
			!pq.empty() && !(pq.top().x == dst_x && pq.top().y == dst_y);)
		{
			eax = pq.top() ,pq.pop();
			for(i = 0;i != 4;i++)
				switch(mapa[eax.x + d[0][i]][eax.y + d[1][i]])
				{
					case '.':
						add; break;
					case 'X':
						add; break;
					case 'Y':
						add; break;
					case 'A':
						if(eax.value % 3 == 0) break;
						else add;
					case 'B':
						if(eax.value % 3 == 1) break;
						else add;
					case 'C':
						if(eax.value % 3 == 2) break;
						else add;
				}
		}
		cout << (pq.empty() ? -1 : pq.top().value - 1) << endl;
	}
}
