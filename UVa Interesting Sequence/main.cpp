#include <iostream>
#include <memory.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int pos[100005];
int main(int argc, char** argv) {
	int T ,n ,ans ,last;
	int i ,tmp;
	for(cin >> T;T--;) {
		cin >> n;
		memset(pos ,-1 ,sizeof(pos));
		for(last = ans = i = 0;i < n;i++) {
			cin >> tmp;
			//cout << pos[tmp] << "qwer" << endl;
			if(pos[tmp] != -1 && pos[tmp] >= last) {
				last = i;
			//	cout << "found: " << i << endl;
				ans += 1;
			}
			pos[tmp] = i;
		}
		cout << ans << endl;
	}
	return 0;
}

// Not tested ,and fuck you, CPE.
