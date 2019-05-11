#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define N 1000000
int data[N] ,pos[N] ,opt[N];
using namespace std;

int main() {
	int t ,n ,eax;			int i ,tmp ,on;
	vector<int>::iterator ptr;
	for(n = 0;cin >> eax;n++) data[n] = eax;
	
	vector<int> lis = vector<int>();
	pos[0] = 0; lis.push_back(data[0]);
	for(i = 1;i != n;i++)
	{
		if(data[i] > lis.back())
		{
			pos[i] = lis.size();
			lis.push_back(data[i]);
		}
		else
		{
			ptr = lower_bound(lis.begin() ,lis.end() ,data[i]);
			*ptr = data[i];
			pos[i] = ptr - lis.begin();
		}
	}
	
	cout << lis.size() << endl << "-" << endl;
	for(i = n - 1, on = lis.size() - 1;i != -1;i--)
		if(pos[i] == on)
		{
			opt[on] = data[i];
			on -= 1;
		}
	
	for(i = 0;i != lis.size();i++)
		cout << opt[i] << endl;
	
	
	return 0;
}
