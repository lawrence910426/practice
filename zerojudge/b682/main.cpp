#include <iostream>
#define abs(a ,b)(a < b ? (b) - (a) : 1440 - ((a) - (b)))
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main() {
	int h1 ,m1 ,h2 ,m2 ,eax;
	while(cin >> h1 >> m1 >> h2 >> m2) 
		eax = abs(h1 * 60 + m1 ,h2 * 60 + m2) ,
		cout << eax / 60 << " " << eax % 60 << endl;  
}
