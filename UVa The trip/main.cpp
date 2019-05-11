#include <iostream>
#include <algorithm>
#define abs(a) (a > 0 ? (a) : -(a))
using namespace std;

bool cmp(int a, int b) { return a > b; }
int main() {
	int data[10000] ,avg ,addition ,n ,ans;
	int i ,eax ,ebx;
	float tmp;
	while(cin >> n) {
		if(n == 0) break;
		
		for(i = 0;i != n;i++) {
			scanf("%f" ,&tmp);
			data[i] = (int)(tmp * 1e2 + 0.4);
		}
		for(avg = i = 0;i != n;i++) avg += data[i];
		addition = avg % n, avg /= n;
		
		sort(data ,data + n, cmp);
		for(ans = i = 0;i != n;i++) {
			if(i < addition) ans += abs(data[i] - avg - 1);
			else ans += abs(data[i] - avg);
			//printf("%d %d %d %d\n" ,ans ,avg ,addition ,data[i]);
		}
		
		tmp = ans; tmp /= 200;
		printf("$%.2f\n" ,tmp);
	}
}
