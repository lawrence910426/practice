#include <iostream>
#include <cmath>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main(int argc, char** argv) {
	int a ,b ,c ,d ,ans ,left_1;
	while(cin >> a >> b >> c >> d)
	{
		ans = left_1 = 0;
		ans += d;
		ans += ceil((double)b / 8) ,left_1 += ceil((double)b / 8) * 64 - b * 8;
		ans += c; left_1 += c * 37;
		ans += (a - left_1 > 0 
					? ceil((a - left_1) / 64)
					: 0);
		cout << ans << endl;
	}
}
