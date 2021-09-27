#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int T;
	int data[3];
	for(cin >> T;T--;) {
		cin >> data[0] >> data[1] >> data[2];
		sort(data, data + 3);
		if(data[0] + data[1] < data[2]) cout << data[0] + data[1] << '\n';
		else cout << (data[0] + data[1] + data[2]) / 2 << '\n';
	}
}
