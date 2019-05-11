#include <iostream>
#define abs(x) (x > 0 ? x : -x)
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

float f(float x) {
	return x * x - 4 * x + 4; 	
}

int main(int argc, char** argv) {
	float l = -10 ,r = 10 ,ll ,rr ,precision = 1e-3;
	while(abs(l - r) > precision) {
		ll = (l + l + r) / 3 ,rr = (l + r + r) / 3;
		if(f(ll) > f(rr)) l = ll;
		if(f(ll) < f(rr)) r = rr;
		if(f(ll) == f(rr)) l = ll ,r = rr;
	}
	cout << f((l + r) / 2) << " " << (l + r) / 2 << endl;
}
