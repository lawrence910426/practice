#include <iostream>
#include <vector>
#include <memory.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
#define N 300
#define adapt(col) (col ? 1 : -1)
vector<int> data[N];
int color[N];
bool visit[N];

int paint(int on ,bool col)
{
	if(color[on] == adapt(col) || color[on] == 0)
		color[on] = adapt(col);
	else return -1;
	if(visit[on]) return 0;
	
	visit[on] = true;
	vector<int> able = data[on];
	for(int i = 0;i != able.size();i++)
		if(paint(able[i] ,!col) == -1) return -1;
	
	return 0;
}

int main() {
	int n ,m;			int i ,eax ,ebx;
	while(cin >> n ,n)
	{
		cin >> m;
		memset(data ,0 ,sizeof(data));
		memset(color ,0 ,sizeof(color));
		memset(visit ,0 ,sizeof(visit));
		for(i = 0;i != m;i++)
			cin >> eax >> ebx ,
			data[eax].push_back(ebx) ,
			data[ebx].push_back(eax);
		cout << (paint(0 ,0) == -1 ? "NOT BICOLORABLE." : "BICOLORABLE.") << endl;
	}
}
