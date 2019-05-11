#include <iostream>
int a[3000][3000] ,b[3000][3000] ,c[3000][3000];

using namespace std;
int main() {
	int n;		int i ,j ,k ,eax;
	while(cin >> n)
	{
		for(i = 0;i != n;i++) for(j = 0;j != n;j++) c[i][j] = 0;
		for(i = 0;i != n;i++) for(j = 0;j != n;j++) cin >> a[i][j];
		for(i = 0;i != n;i++) for(j = 0;j != n;j++) cin >> b[i][j];
		for(i = 0;i != n;i++) for(j = 0;j != n;j++) for(k = 0;k != n;k++) 
			c[i][j] += a[i][k] + b[k][j];
		
		cout << "YES" << endl; continue;
		No:
		cout << "NO" << endl;
		
	}
}
