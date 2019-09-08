#include <iostream>
#include <memory.h>
#include <algorithm>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int data[1000000];
int main() {
	int n ,m ,ans;	int i ,eax ,j;
	while(cin >> n >> m)
	{
		for(i = 0;i != m;i++) cin >> eax ,data[i] = eax * 2 ,cin >> eax ,data[i + m] = eax * 2 + 1;
		sort(data ,data + 2 * m);
		for(ans = 0 ,i = 2;i != (n + 1) * 2;i += 2)
			ans += ((upper_bound(data ,data + 2 * m ,i) - data) % 2 == 0 ? 1 : 0);
		cout << ans << endl;
	}
}
