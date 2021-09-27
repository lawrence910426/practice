#include <iostream>
#include <map>
#include <set>

using namespace std;

map<long long, set<long long> > matrix;
void Remove(long long x, long long y) { if(matrix.find(x) != matrix.end()) matrix[x].erase(y); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	long long x, y;
	for(cin >> T;T--;) {
		string op;
		cin >> op;
		if(op == "PrintEnd") {
			cout << op << '\n';
			for(auto it = matrix.rbegin();it != matrix.rend();it++)
				for(auto ptr = it->second.rbegin();ptr != it->second.rend();ptr++)
					cout << '(' << *ptr << "," << it->first << ')' << '\n';
		} else if(op == "PrintFront") {
			cout << op << '\n';
			for(auto it = matrix.begin();it != matrix.end();it++)
				for(auto ptr = it->second.begin();ptr != it->second.end();ptr++)
					cout << '(' << *ptr << "," << it->first << ')' << '\n';
		} else if(op == "House") {
			cin >> y >> x;
			if(matrix.find(x) == matrix.end()) matrix[x] = set<long long>();
			matrix[x].insert(y);
		} else if(op == "Bomb") {
			cin >> y >> x;
			long long d[2][5] = {{0, 1, -1, 0, 0}, {0, 0, 0, 1, -1}};
			for(int i = 0;i < 5;i++) Remove(x + d[0][i], y + d[1][i]);
		}
	}
}
