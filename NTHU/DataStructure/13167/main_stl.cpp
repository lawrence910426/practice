#include <list>
#include <iostream>
#include <vector>

using namespace std;

list<pair<long long, list<long long> > > Matrix;

inline void Remove(long long X, long long Y) { 
	for(auto it : Matrix) if(it.first == X) 
		for(auto ptr = it.second.begin();ptr != it.second.end();ptr++) if(*ptr == Y) 
			it.second.erase(ptr); 
}

vector<pair<long long, long long> > Data() {
	vector<pair<long long, long long> > ans;
	for(auto it : Matrix) for(auto ptr : it.second) ans.push_back({it.first, ptr});
	return ans;
}

int main() {
	int T;
	long long x, y;
	for(cin >> T;T--;) {
		string op;
		cin >> op;
		if(op == "PrintEnd") {
			auto ans = Data();
			for(int i = ans.size() - 1;i >= 0;i--) cout << ans[i].first << " " << ans[i].second << endl;
		} else if(op == "PrintFront") {
			auto ans = Data();
			for(int i = 0;i < ans.size();i++) cout << ans[i].first << " " << ans[i].second << endl;
		} else if(op == "House") {
			cin >> x >> y;
			if(Matrix.empty()) Matrix.push_back({x, list<long long>()});
			auto it = Matrix.begin();
			while(it != Matrix.end()) {
				if(it->first < x && (next(it) == Matrix.end() || x < next(it)->first)) {
					Matrix.insert(it, {x, list<long long>()});
					break;
				} else if(it->first == x) break;
				it = next(it);
			}
			
			auto col = it->second;
			for(auto ptr = col.begin();ptr != it->second.end();ptr++) 
				if(*ptr < y && y < *next(ptr)) 
					col.insert(ptr, y);
		} else if(op == "Bomb") {
			cin >> x >> y;
			Remove(x, y);
			Remove(x + 1, y);
			Remove(x - 1, y);
			Remove(x, y + 1);
			Remove(x, y - 1);
		}
		cout << op << endl;
	}
}
