#include <iostream>
#include <cmath>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define fix(a) (((float)((int)(a * 1000) % 10 >= 5 ? (int)(a * 100) + 1 : (int)(a * 100))) / 100)
using namespace std;
int main(int argc, char** argv) {
	float f;
	while(cin >> f)
		if(fix(acos(asin(f)) * 180 / M_PI) < -1) cout << "FAIL!" << endl;
		else printf("%0.2f\n" ,fix(acos(asin(f)) * 180 / M_PI));
}
