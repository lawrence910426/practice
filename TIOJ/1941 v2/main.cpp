#include <bits/stdc++.h>
using namespace std;

class BIT{
	private:
		int n;
		vector<int> arr;
		inline int lowbit(int x){return x&(-x);}
		void modify(int p, int x){
			for(;p;p-=lowbit(p)) arr[p] += x;
		}
	public:
		void init(int n_){
			n = n_; arr.clear();
			arr.resize(n);
		}
		void modify(int l, int r, int v){
			modify(l, -v);
			modify(r, v);
		}
		int query(int x){
			int ret = 0;
			for(;x<n;x+=lowbit(x)) ret += arr[x];
			return ret;
		}
} bit;

set<int> st;

int main(){
	int n; scanf("%d", &n);
	bit.init(n+1); st.insert(n);
	for(int i=0;i<n;i++){
		int l, r; scanf("%d%d", &l, &r);
		if(l == 0 && r == 0) break;
		st.insert(l);
		auto it = st.upper_bound(r);
		bit.modify(l, *it, 1);
		int cur = bit.query(*it);
		for(;it!=prev(st.end());it=st.erase(it)){
			int nv = bit.query((*it)+1);
			if(nv > cur) break;
			bit.modify(*it, *next(it), cur-nv);
		}
	}
	printf("%d\n", bit.query(n));
	return 0;
}
