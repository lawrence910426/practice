#include <iostream>
#include <cstring>
#define idx (s.length() + 1 - i)
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int modular(int digit ,int g)
{
	int ret = 1;
	while(digit--)
		ret <<= 8 ,ret %= g;
	return ret;
}

int main(int argc, char** argv) {
	string s;
	long long int g ,sum;
	long long int i ,tmp;
	
	while(cin >> s >> g)
	{
		for(sum = i = 0;i != s.length();i++)
		{
			tmp = s[i] * modular(idx ,g),
			//printf("%d %d\n" ,s[i] ,idx),
			tmp %= g,
			sum += tmp;
			sum %= g;
		}
		//printf("%d\n" ,sum);
		printf("%x\n" ,g - (sum % g));
	}
}
