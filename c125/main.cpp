#include <iostream>
#include <queue>
#include <cmath>
#include <memory.h>
/* zerojudge c125. This run with dijkstra algorithm. */
/* But it gets an WA. fuck. */

using namespace std;

struct stone{
	int x ,y ,code;
	double frog_d;
	bool operator< (stone s)const{
		return s.frog_d < frog_d;
	}
}data[500];
bool visit[500];

#define INF 10000
#define dist(a ,b) sqrt(abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y))

int main() {
	int n ,counter;						int i;	double eax;
	priority_queue<stone> next;	vector<stone> tmp;
	while(memset(data ,0 ,sizeof(data)) ,memset(visit ,0 ,sizeof(visit))
		,cin >> n ,n)
	{
		for(i = 0;i != n;i++) cin >> data[i].x >> data[i].y ,data[i].frog_d = INF ,data[i].code = i;
		while(!next.empty()) next.pop();
		for(i = 1;i != n;i++)
			data[i].frog_d = dist(data[0] ,data[i])
			,next.push(data[i]);
		
		for(;!next.empty()
			&& !(next.top().x == data[n - 1].x && next.top().y == data[n - 1].y);)
		{
			visit[next.top().code] = true;
			for(tmp = vector<stone>() ,i = 1;i != n;i++)
			{
				if(visit[i]) continue;
				eax = dist(data[i] ,next.top());
				
				if(max(eax ,next.top().frog_d) < data[i].frog_d)
					data[i].frog_d = max(eax ,next.top().frog_d)
					,tmp.push_back(data[i]);
			}
			
			//cout << next.top().x << "\t" << next.top().y << "\t" << next.top().frog_d << "\t" << next.top().code << endl;
			for(next.pop() ,i = 0;i != tmp.size();i++)
				//cout << tmp[i].x << "\t" << tmp[i].y << "\t" << tmp[i].frog_d << "\t" << tmp[i].code << endl
				next.push(tmp[i]);
			//cout << endl;
		}
		
		printf("Scenario #%d\nFrog Distance = %.3f\n\n" ,++counter ,next.top().frog_d);
	}
}
