#include <iostream>
#define M 131071
using namespace std;

int main() {
	register char eax;
	int leftover;
	while(scanf("%c" ,&eax) != EOF) {
		leftover = (eax == '0' ? 0 : 1);
		while(scanf("%c" ,&eax) ,eax != '#') {
			leftover <<= 1;
			leftover += (eax == '0' ? 0 : 1);
			leftover %= M;
		}
		scanf("%c" ,&eax); //read the \n symbol
		printf(leftover == 0 ? "YES\n" : "NO\n");
	}
}
