#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	long long int dp[35] = {0 ,0 ,3 ,0 ,11} ,n;
	for(int i = 6;i != 35;i++) dp[i] = 4 * dp[i - 2] - dp[i - 4];
	while(std::cin >> n ,n != -1)
		std::cout << (n == 0 ? 1 : 
			(dp[n] == 0 ? 0 : dp[n])
		) << std::endl;
}
