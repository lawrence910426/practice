#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int main(int argc, char** argv) {
	int n ,m ,k ,ans;		int shift;
	while(cin >> n >> m >> k) {
		shift = k - 1;
		ans = (m % (n - shift)) + 1;
		
		while(shift--) {
			cout << ans << "\t" << (ans + m) << "\t" << (n - shift) << endl;
			ans = (ans + m) % (n - shift + 1);
			if(ans == 0) ans = n;
		}
			
		
		cout << ans << endl;
	}
}
