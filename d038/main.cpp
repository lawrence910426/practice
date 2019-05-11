#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int main() {
	long long int dp[55] = {0 ,1 ,2};
	for(int i = 3; i != 55;i++) dp[i] = dp[i - 1] + dp[i - 2];
	int eax = 0;
	while(cin >> eax ,eax) cout << dp[eax] << endl;
}
