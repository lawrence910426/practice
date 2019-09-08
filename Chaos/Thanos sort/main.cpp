#include <iostream>
using namespace std;
int data[1000];

int ans(int l ,int r) {
	if(r - l == 1) return 1;
	bool AC = true;
	for(int i = l;i < r - 1;i++) 
		AC &= data[i] <= data[i + 1];
	if(AC) return r - l;
	else {
		int left = ans(l ,(l + r) / 2);
		int right = ans((l + r) / 2 ,r);
		return (left > right ? left : right);
	}
}

int main() {
	int n ,i;
	while(cin >> n) {
		for(i = 0;i < n;i++) cin >> data[i];
		cout << ans(0 ,n) << endl;	
	}
	
}
