#include <iostream>
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main() {
	int n ,count;		int i ,j;
	string data[50] = {"" ,"1"} ,tmp;	char last;
	for(i = 2;i != 45;i++)
	{
		count = 1; last = data[i - 1][0];
		for(j = 1;j != data[i - 1].length();j++)
			if(last == data[i - 1][j])
				count++;
			else
			{
				tmp = (char)(count + '0');
				tmp += last;
				data[i] += tmp;
				count = 1; last = data[i - 1][j];
			}
		tmp = (char)(count + '0');
		tmp += last;
		data[i] += tmp;
	}
	while(cin >> n) cout << data[n] << endl;
}
