#include <iostream>
#include <memory.h>
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define N 10000000
int back[N] ,group_last[2000] ,group[N] ,first ,last;

using namespace std;
int main() {
	int groups ,counter = 0;		int i ,p ,eax;		string cmd;
	ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
	while(memset(back ,-1 ,sizeof(back)) ,memset(group_last ,-1 ,sizeof(group_last)) ,memset(group ,0 ,sizeof(group)),first = last = -1
		,cin >> groups)
	{
		cout << "Line #" << ++counter << endl;
		for(i = 1;i != groups + 1;i++)
		{
			cin >> p;
			while(p--) cin >> eax ,group[eax] = i;
		}
		while(true)
		{
			if(cin >> cmd ,cmd == "STOP") break;
			if(cmd == "ENQUEUE")
			{
				if(cin >> eax, first == -1)
				{
					first = last = eax ,back[eax] = -1;
					if(group[eax]) group_last[group[eax]] = eax;
				}
				else if(group_last[group[eax]] == last || group_last[group[eax]] == -1)
				{
					last = back[last] = eax;
					if(group[eax]) group_last[group[eax]] = eax;
					back[eax] = -1;
				}
				else
					back[eax] = back[group_last[group[eax]]] ,
					group_last[group[eax]] = back[group_last[group[eax]]] = eax;
			}
			if(cmd == "DEQUEUE")
			{
				cout << first << endl;
				if(group_last[group[first]] == first) group_last[group[first]] = -1;
				first = back[first];
			}
		}
	}
}
