#include <iostream>
#include <memory.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main(int argc, char** argv) {
	int number[3005] ,ans[1005] ,N;
	int i ,j;
	
	memset(number ,0 ,sizeof(number));
	memset(ans ,0 ,sizeof(ans));
	number[0] = ans[0] = 1;
	for(i = 1;i < 1005;i++) {
		for(j = 0;j < 3000;j++) number[j] *= i;
		for(j = 0;j < 3005;j++) {
			number[j + 1] += number[j] / 10;
			number[j] %= 10;
		}
		for(j = 0;j < 3005;j++) ans[i] += number[j];
	}
	
	while(cin >> N) cout << ans[N] << endl;
}
