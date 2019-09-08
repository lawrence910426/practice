#include <iostream>
#include <memory.h>
#include <algorithm>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int data[1000000] ,weight[1000000] ,mouses[1000000];
using namespace std;

bool comp(int a ,int b)
{
	return a > b;
}
int main() {
	long long colors ,seats ,on ,dist ,ans;			int i ,j;
	while(memset(data ,0 ,sizeof(data))
		,cin >> colors >> seats >> on >> dist)
	{
		seats *= 3;
		
		for(i = 0;i != colors;i++) cin >> data[i];
		sort(data ,data + colors ,comp);
		for(memset(weight ,0 ,sizeof(weight)) ,i = on - 1;i != seats;i++) weight[i] = i - (on - 1);
		for(memset(mouses ,0 ,sizeof(mouses)) ,i = 0 ,j = 0;i < seats;i += dist) mouses[i] = data[j++];
		for(ans = 0, i = 0;i != seats;i++) ans += mouses[i] * weight[i];
		cout << ans << endl;
	}
}


// 1 2 3 4
// 4 3 2 1
// 0 0 0 0 * 1 2 3 4 5
// 4     3     2     1
