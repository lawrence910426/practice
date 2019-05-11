#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
long long int day[150] ,night[150] ,n ,t ,r;
#define Z(x) (x > 0 ? x : 0)

int main() {
	long long int i ,j ,ans ,best ,index;
	while(memset(day ,0 ,sizeof(day)), memset(night ,0 ,sizeof(night))
		,cin >> n >> t >> r ,!(n == 0 && t == 0 && r == 0))
	{
		for(i = 0;i != n;i++) cin >> day[i];
		for(i = 0;i != n;i++) cin >> night[i];
		
		for(i = 0;i != n;i++)
			if(day[i] + night[i] > t)
			{
				/*for(ans = 0,j = 0;j != n;j++) cout << day[j] << "\t" << night[j] << endl;
				cout << endl; system("pause");
				
				for(j = 0;j != n;j++) //both relax
					if(day[i] + night[j] <= t && day[j] + night[i] <= t)
						swap(night[i] ,night[j]);
				if(day[i] + night[i] <= t) continue;*/
				
				for(best = Z(day[i] + night[0] - t) + Z(day[0] + night[i] - t) ,index = 0
					,j = 0;j != n;j++) //one relax ,one tired
					if(Z(day[i] + night[j] - t) + Z(day[j] + night[i] - t) < best)
						best = Z(day[i] + night[j] - t) + Z(day[j] + night[i] - t)
						,index = j;
				
				if(best < Z(day[i] + night[i] - t) + Z(day[index] + night[index] - t))
					swap(night[i] ,night[index]);	 
			}
		
		
		//for(ans = 0,i = 0;i != n;i++) cout << day[i] << "\t" << night[i] << endl;
		for(ans = 0,i = 0;i != n;i++)
			ans += Z(day[i] + night[i] - t) * r;
		cout << ans << endl;
			
	}
}
