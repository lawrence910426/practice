#include <iostream>
#include <bitset>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
bitset<1000000> dp;
int main() {
	int V ,n ,eax;
	while(cin >> V >> n)
	{
		while(n--) cin >> eax ,dp |= dp << eax ,dp[eax] = true;
		for(eax = V + 1;eax--;) if(dp[eax]) {
			cout << V - eax << endl;
			break;
		}
	}
}
