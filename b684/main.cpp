#include <iostream>
#include <map>
using namespace std;

int data[100000000];
int main()
{
	int n ,last ,ans;		int i ,tmp;		bool dir;
	while(cin >> n)
	{
		for(i = 0;i != n;i++) cin >> tmp ,data[tmp] = i;
		for(ans = 0 ,i = 2 ,last = data[1] ,dir = true;i != n + 1;i++)
			if(dir)
				if(last < data[i]) last = data[i];
				else dir = !dir ,last = data[i] ,ans += 1;
			else
				if(last > data[i]) last = data[i];
				else dir = !dir ,last = data[i] ,ans += 1;
		cout << ans << endl;
	}
}
