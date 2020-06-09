#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
long long int dp[100];
int main(int argc, char** argv) {
	dp[1][1] = dp[2][1] = dp[2][0] = 1;
	int i;
	for(i = 3;i != 100;i++) 
		dp[i] = dp[i - 2] + dp[i - 3];
}
