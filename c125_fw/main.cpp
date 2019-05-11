#include <iostream>
#include <cmath>

struct stone{
	int x ,y;
};

/* zerojudge c125. Written in Floyd-warshall. */
/* short ,clean ,but slow */
/* but ofcourse ,i still got an WA. */
/* fuck you. */

#define INF 10000
#define dist(a ,b) sqrt(abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y))

using namespace std;
int main() {
	int n ,counter = 0;				int i ,j ,k;
	double fw[500][500]; stone data[500];
	while(cin >> n ,n)
	{
		for(i = 0;i != n;i++) cin >> data[i].x >> data[i].y;
		for(i = 0;i != n;i++) for(j = 0;j != n;j++) fw[i][j] = dist(data[i] ,data[j]);
		
		for(k = 0;k != n;k++)
			for(i = 0;i != n;i++) for(j = 0;j != n;j++)
				fw[i][j] = min(fw[i][j] ,max(fw[i][k] ,fw[k][j]));
		
		printf("Scenario #%d\nFrog Distance = %.3f\n\n" ,++counter ,min(fw[0][n - 1] ,fw[n - 1][0]));
	}
}
