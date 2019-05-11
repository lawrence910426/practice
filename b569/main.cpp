#include <iostream>
#include <cstring>
#include <bitset>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
bitset<10000050> start ,data;

int main() {
	int i; register char eax;	string tmp;
	while(getline(cin ,tmp))
	{
		for(i = 0;i != tmp.length();i++) start[i] = tmp[i] == '1';
		for(getline(cin ,tmp) ,i = 0;i != tmp.length();i++) data[i] = tmp[i] == '1';
		for(i = 0;i != tmp.length();i++) if(start[i]) data[i] = !data[i];
		for(i = 0;i != tmp.length();i++) 
			if(data[i]) data[i] = false;
			else {	data[i] = true;break;	}
		for(i = 0;i != tmp.length();i++) if(start[i]) data[i] = !data[i];
		for(i = 0;i != tmp.length();i++) cout << (data[i] ? '1' : '0');
		cout << endl;
	}
}
