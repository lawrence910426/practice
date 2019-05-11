#include <iostream>
#include <memory.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int coin[5] = {50, 25, 10, 5 ,1};
unsigned long long int dp[80000];
using namespace std;

int main(int argc, char** argv) {
	memset(dp ,0 ,sizeof(dp)); dp[0] = 1;
	for(int i = 0;i != 5;i++)
		for(int j = 0;j != 50000;j++)
			if(dp[j] != 0) dp[j + coin[i]] += dp[j];
	int eax;
	while(cin >> eax)
		if(dp[eax] == 1) printf("There is only 1 way to produce %d cents change.\n" ,eax);
		else printf("There are %lld ways to produce %d cents change.\n" ,dp[eax] ,eax);
}
