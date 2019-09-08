#include <iostream>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct ptr {
	int prev ,next ,value ,index;
}data[200000];
int main(int argc, char** argv) {
	int n ,m ,k;		int i ,on;		ptr tmp[3];
	while(cin >> n >> m >> k) {
		for(i = 0;i != n;i++) {
			data[i].index = data[i].value = i;
			data[i].next = (i == n - 1 ? 0 : i + 1);
			data[i].prev = (i == 0 ? n - 1 : i - 1);
		}
		
		on = n - 1;
		while(k--) {
			for(i = 0;i != m;i++)
				on = data[on].next;
			
			tmp[0] = data[data[on].prev];
			tmp[1] = data[on];
			tmp[2] = data[data[on].next];
			
			data[on].next = tmp[2].index;
			data[on].prev = tmp[0].index;
			data[tmp[1].prev].next = tmp[1].next;
			data[tmp[1].next].prev = tmp[1].prev;
			
			//cout << on << endl;
		}
		cout /*<< "ans:"*/ << data[data[on].next].value + 1 << endl;
	}
}

