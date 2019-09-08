#include <iostream>

using namespace std;

int main() {
	int modulo ,ans ,leftover ,modded;
	while(cin >> modulo) {
		modded = leftover = 1;
		for(ans = 1;leftover != 0;ans++) {
			modded = modded * 10 % modulo;
			modded %= modulo;
			
			leftover += modded;
			leftover %= modulo;
			
			/*cout << leftover << endl;
			system("pause");*/
		}
		cout << ans << endl;
	}
}
