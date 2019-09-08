#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;
int data[1005][1005] ,d[2][4] = {{0 ,0 ,1, -1} ,{1 ,-1 ,0 ,0}};
bool visit[1005][1005];
struct pt{
	int x, y ,value;
	bool operator<(pt eax)const{
		return value > eax.value;
	}
};

int main() {
	int t ,n ,m; 		int i ,j;		pt eax ,tmp;
	cin >> t;
	while(t--)
	{
		for(cin >> n >> m ,i = 0;i != n;i++) for(j = 0;j != m;j++) cin >> data[i + 1][j + 1];
		priority_queue<pt> pq; eax.x = eax.y = 1 ,eax.value = data[1][1] ,pq.push(eax);
		for(memset(visit ,0 ,sizeof(visit)) ,visit[1][1] = true;!(pq.top().x == n && pq.top().y == m);)
			for(tmp = pq.top(),pq.pop() ,i = 0;i != 4;i++)
			{
				eax.x = tmp.x + d[0][i];
				eax.y = tmp.y + d[1][i];
				if(eax.x == 0 || eax.x == n + 1 || eax.y == 0 || eax.y == m + 1 || visit[eax.x][eax.y]) continue;
				eax.value = tmp.value + data[eax.x][eax.y];
				visit[eax.x][eax.y] = true;
				pq.push(eax);
			}
				
		cout << pq.top().value << endl;
	}
}
