#include <iostream>
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
long long int fab[100];
string show(int l, int r, int n) {
	//printf("%d %d %d %d\n" , n ,l ,r ,fab[n - 2]);
	//system("pause");
	
	if(n == 0) {
		return "0";
	}
	if(n == 1) {
		return "1";
	}
	
	string ret = "";
	if(l < fab[n - 2] && r < fab[n - 2]) {
		ret += show(l ,r ,n - 2);	
	} 
	if(l < fab[n - 2] && fab[n - 2] <= r) {
		ret += show(l ,fab[n - 2] - 1 ,n - 2);	
		ret += show(0 ,r - fab[n - 2] ,n - 1);
	}
	if(fab[n - 2] <= l && fab[n - 2] <= r) {
		ret += show(l - fab[n - 2] ,r - fab[n - 2] ,n - 1);
	}
	return ret;
}

int main() {
	int i;
	fab[0] = fab[1] = 1;
	for(i = 2;i < 50;i++) fab[i] = fab[i - 1] + fab[i - 2]; 
	
	int T ,l ,r ,n;
	for(cin >> T;T--;)
		cin >> n >> l >> r ,cout << show(l ,r ,n) << endl;
}
