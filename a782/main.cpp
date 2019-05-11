#include <iostream>
#include <sstream>
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main() {
	string eax ,ans ,last;
	while(getline(cin ,eax))
	{
		if(eax == "END") break;
		stringstream ss(eax);
		while(ss >> last) ans += (last[0] + ('A' - 'a'));
		cout << ans << " " << last << endl;
		ans = last = "";
	}
}
