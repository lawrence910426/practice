#include <iostream>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
long long int stair(int i)
{
	if(i == 0 || i == 1) return 1;
	return i * stair(i - 1);
}

int main(int argc, char** argv) {
	char cmd;	int a ,b;
	while(cin >> cmd) 
	{
		cin >> a >> b;
		switch(cmd)
		{
			case 'C':
				cout << stair(a) / stair(b) / stair(a - b) << endl;
				break;
			case 'P':
				cout << stair(a) / stair(a - b) << endl;
				break;
			case 'H':
				cout << stair(a + b - 1) / stair(b - 1) / stair(a) << endl;
				break;
		}
	}
	return 0;
}
