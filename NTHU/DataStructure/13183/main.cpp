#include <iostream>
#include <set>

using namespace std;

int main() {
	int T;
	string op;
	long long x, d;
	set<long long> ans;
	for(cin >> T;T--;) {
		cin >> op;
		if(op == "PrintFront") {
			cout << op << '\n';
			for(auto it = ans.begin();it != ans.end();it++) cout << *it << '\n';
		} else if(op == "PrintEnd") {
			cout << op << '\n';
			for(auto it = ans.rbegin();it != ans.rend();it++) cout << *it << '\n';
		} else if(op == "House") {
			cin >> x;
			ans.insert(x);
		} else if(op == "Bomb") {
			cin >> x >> d;
			for(long long i = x - d;i <= x + d;i++) ans.erase(i);
		}
	}
}
