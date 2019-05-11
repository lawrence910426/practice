#include <iostream>

using namespace std;

int main() {
	int n ,data[100] ,ca = 1;
	int i ,j;
	long long best ,now;
	while(cin >> n) {
		for(i = 0;i != n;i++) cin >> data[i];
		for(best = i = 0;i != n;i++) {
			now = 1;
			for(j = i;j != n;j++) 
			{
				now *= data[j];
				if(best < now) best = now;
			}
		}
		cout << "Case #"<<ca++<<": The maximum product is "<<best<<"."<<endl <<endl;
	}
}
