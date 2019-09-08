#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
long long int day[150] ,night[150] ,n ,t ,r;
#define Z(x) (x > 0 ? x : 0)
#define INF 9223372036854775807

int main() {
	long long int i ,j ,ans = INF ,best ,index;
	while(memset(day ,0 ,sizeof(day)), memset(night ,0 ,sizeof(night))
		,cin >> n >> t >> r ,!(n == 0 && t == 0 && r == 0))
	{
		for(i = 0;i != n;i++) cin >> day[i];
		for(i = 0;i != n;i++) cin >> night[i];
		
		sort(night ,night + n);
		do
		{
			for(best = 0,j = 0;i != n;j++)
				best += Z(day[j] + night[j] - t) * r;
			ans = min(best ,ans);
		}while(next_permutation(night ,night + (n > 10 ? 10 : n)));
		
		
		//for(ans = 0,i = 0;i != n;i++) cout << day[i] << "\t" << night[i] << endl;
		for(ans = 0,i = 0;i != n;i++)
			ans += Z(day[i] + night[i] - t) * r;
		cout << ans << endl;
			
	}
}
