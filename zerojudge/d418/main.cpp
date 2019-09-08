#include <iostream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int main(int argc, char** argv) {
	long long int n ,N ,i;
	cin >> n;
	int data[2][8] = {{2,3,4,5,6,7,8,9},{0,0,0,0,0,0,0,0}};
	while(n--)
	{
		cin >> N;
		if(N == 1)
		{
			cout << "-1\n";
			continue;
		}
		for(i = 7;i != -1;i--) data[1][i] = 0;
		for(i = 7;i != -1;i--) while(N % data[0][i] == 0) data[1][i] += 1, N /= data[0][i];
		if(N!=1) cout << "-1";
		else for(i = 0;i != 8;i++) while(data[1][i]--) cout << data[0][i];
		cout << endl;
	}
	return 0;
}
