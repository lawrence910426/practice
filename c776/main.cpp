#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main(int argc, char** argv) {
	int n ,m;
	while(cin >> n >> m)
		cout << 3 * n * m + m + 2 * n << endl;
}
