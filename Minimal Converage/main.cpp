#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

#define INF (1LL << 31) - 1
struct p {
	int l ,r;
}data[1000005];

bool cmp(p a ,p b) {
	if(a.l == b.l) return a.r < b.r;
	return a.l < b.l;
}

int main() {
	int T ,n ,L ,R ,m ,maxi;
	int i;
	for(cin >> T;T--;) {
		cin >> m;
		for(n = 0; cin >> data[n].l >> data[n].r ,!(data[n].l == 0 && data[n].r == 0); n++) ;
		sort(data ,data + n ,cmp);
		
		vector<int> ans;
		L = -INF ,R = 0;
		for(i = 0;i < n;i++) {
			if(m <= R) {
				break;	
			}
			if(data[i].l <= R && R <= data[i].r) {
				maxi = i;
				while(i < n && data[i].l <= R)  {
					if(data[i].r > data[maxi].r) maxi = i;
					i += 1;
				}
				i -= 1;
				
				ans.push_back(maxi);
				R = data[maxi].r;
			}
		}
		
		if(m <= R) {
			cout << ans.size () << endl;
			for(i = 0;i != ans.size();i++) cout << data[ans[i]].l << " " << data[ans[i]].r << endl;	
		}
		else cout << "0" << endl;
		if(T != 0)cout << endl;
	}
}

/*
2

1
-1 0
-5 -3
2 5
0 0

1
-1 0
0 1
0 0

*/
