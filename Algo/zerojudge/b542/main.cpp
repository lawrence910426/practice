#include <iostream>
#include <algorithm>
using namespace std;
int n ,data[1000000] ,q;
bool solve()
{
	int i ,j;	i = j = 0;
	while(i < n && j < n)
	{
		if(i == j) i++;
		else if(data[i] - data[j] < q) i++;
		else if(data[i] - data[j] > q) j++;
		else if(data[i] - data[j] == q) return true;
	}
	return false;
}
int main() {
	int querys ,i;
	while(cin >> n >> querys)
	{
		for(i = 0;i != n;i++) cin >> data[i];
		sort(data ,data + n);
		while(querys--) cin >> q ,cout << (solve() ? "YES" : "NO") << endl;
	}
}
