#include <iostream>
#include <memory.h>

using namespace std;
#define N 100007
int data[50];
int main() {
	int M ,tmp ,sum;	int i ,j;
	while(cin >> M)
	{
		for(sum = i = 0;i != M;i++) cin >> data[i] ,sum += data[i];
		for(i = 0;i != (1 << (M + 1));i++)
		{
			for(tmp = 0 ,j = 0;j != M;j++)
				if((i >> j) && 1)
					tmp += data[j];
			if((tmp % N) == ((sum - tmp) % N)) goto Yes;
		}
		
		cout << "NO" << endl; continue;		
	Yes:
		cout << "YES" << endl;
	}
}
