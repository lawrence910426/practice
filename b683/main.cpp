#include <iostream>
#include <memory.h>
#include <queue>

using namespace std;
bool mapa[10000][10000];
int value[10000][10000];
int d[2][4] = {{0 ,0 ,1 ,-1} ,{1 ,-1 ,0 ,0}};
#define make eax.x = tmp.x + d[0][k] ,eax.y = tmp.y + d[1][k] ,eax.value = tmp.value + 1

struct pt{
	int x ,y ,value;
	bool operator< (pt eax)const {
		return eax.value < value;
	}
};
int main() {
	int h ,w ,ans;		int i ,j ,k;	register char status;	unsigned long long int mul ,sum ,times;	pt tmp ,eax;
	while(memset(mapa ,0 ,sizeof(mapa)) ,memset(value ,-1 ,sizeof(value)) ,cin >> h >> w)
	{
		for(i = 1;i <= h;i++) for(j = 1;j <= w;j++) cin >> status ,mapa[i][j] = status == '.';
		for(i = 1;i <= max(h ,w);i++) mapa[0][i] = mapa[i][0] = mapa[h + 1][i] = mapa[i][w + 1] = false;
		for(i = 0;i <= h + 1;cout << endl ,i++) for(j = 0;j <= w + 1;j++) cout << (mapa[i][j] ? '.' : '#');
		for(mul = 1 ,i = sum = times = 0;i <= h;i++) for(j = 0;j <= w;j++) if(mapa[i][j])
		{
			priority_queue<pt> pq; ans = -1;
			for(tmp.x = i ,tmp.y = j ,tmp.value = 1 ,pq.push(tmp);!pq.empty();)
			{
				tmp = pq.top() ,pq.pop() ,value[tmp.x][tmp.y] = tmp.value ,mapa[tmp.x][tmp.y] = false;
				for(k = 0;k != 4;k++) 
					if(mapa[tmp.x + d[0][k]][tmp.y + d[1][k]])
						make, pq.push(eax);
					else if(value[tmp.x + d[0][k]][tmp.y + d[1][k]] != -1)
						ans = max(ans ,value[tmp.x + d[0][k]][tmp.y + d[1][k]] + tmp.value - 1);
			}
			if(ans != -1) times += 1 ,mul *= ans ,sum += ans;
		}
		printf("%d %d %lld\n" ,times ,sum ,mul);
	}
}

/*
5 6
######
...#..
.#.###
...#.#
####.#

3 3
...
.#.
...

The problem is not clear enough. Not going to solve the problem. 
*/
