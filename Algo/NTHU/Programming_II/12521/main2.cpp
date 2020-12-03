#pragma GCC optimize("Ofast")

#include <set>
#include <iostream>
#include <cstring>

using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int Q;
	cin >> Q;
	string cmd;
	set<int> S;
	while(Q--) {
		cin >> cmd;
		if(cmd == "print") {
			if(!S.empty()) for(auto it = S.begin();it != S.end();cout << (++it == S.end() ? '\n' : ' ')) cout << *it;
		} else if(cmd == "insert") {
			int x;
			cin >> x;
			S.insert(x);
		} else if(cmd == "min") {
			if(!S.empty()) cout << *S.begin() << '\n';
		} else if(cmd == "range_erase") {
			int l, r;
			cin >> l >> r;
			S.erase(S.lower_bound(l), S.upper_bound(r));
		}
	}
}

