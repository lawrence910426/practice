#include <iostream>
#include <bitset>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

bitset<10000> dp;
int main(int argc, char** argv) {
	int t ,req, bars; 			int i ,eax;cin >> t;
	while(t--)
	{
		dp.reset() ,dp[0] = true;
		cin >> req >> bars; while(bars--) cin >> eax ,dp |= (dp << eax);
		cout << (dp[req] ? "YES" : "NO") << endl;
	}
	return 0;
}


char data[100] = "aoiusddhfuisd";
sort(data ,data + 100);

