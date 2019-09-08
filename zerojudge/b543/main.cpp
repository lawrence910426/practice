#include <iostream>
#include <memory.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct e{
	int level ,power ,defense;
	bool operator<(e eax)const{
		return eax.level > level && eax.power > defense;
	}
}data[10000];
bool visit[10000];
int t ,n ,ans ,s;

int dfs(int boss)
{
	visit[boss] = true;
	int ret = 1;
	for(int i = 1;i != n + 1;i++)
		if(data[i] < data[boss] && !visit[i])
			ret += dfs(i);
	return ret;
}
int main() {
	cin >> t;		int i;
	while(t--)
	{
		for(memset(visit ,0 ,sizeof(visit)) ,i = 1 ,cin >> n;i != n + 1;i++) cin >> data[i].level >> data[i].power >> data[i].defense;
		cin >> s;
		cout << dfs(s) << endl;
	}
	return 0;
}
