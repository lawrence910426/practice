#include <iostream>
#include <algorithm>
using namespace std;
int n ,m ,data[100000];

bool cmp(int a ,int b) {
	if(a % m == b % m) {
		if(a % 2 == 1 && b % 2 == 1) return a > b;
		else if(a % 2 == 0 && b % 2 == 0) return a < b;
		else return a % 2 > b % 2;
	} else return a % m < b % m;
}

int main() {
	int i;
	while(cin >> n >> m ,!(n == 0 && m == 0)) {
		for(i = 0;i != n;i++) cin >> data[i];
		sort(data ,data + n ,cmp);
		
		cout << n << ' ' << m << endl;
		for(i = 0;i != n;i++) cout << data[i] << endl;
		cout << "0 0\n";		
	}
}
