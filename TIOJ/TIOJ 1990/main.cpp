#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
string data[5000500];
int n ,m ,row[5000500] ,col[5000050] ,q;
int main() {
	int i ,j ,x1 ,y1 ,x2 ,y2;		char cmd;
	while(cin >> n >> m)
	{
		for(i = 0;i != n;i++) for(j = 0;j != m;j++) cin >> data[i * m + j];
		for(i = 1;i != max(n ,m) + 1;i++) row[i] = col[i] = i - 1;
		for(cin >> q;q--;)
		{
			cin >> cmd;
			if(cmd == 'S') cin >> x1 >> y1 >> x2 >> y2, swap(data[row[x1] * m + col[y1]] ,data[row[x2] * m + col[y2]]);
			if(cmd == 'R') cin >> x1 >> x2 ,swap(row[x1] ,row[x2]);
			if(cmd == 'C') cin >> y1 >> y2 ,swap(col[y1] ,col[y2]);
		}
		for(i = 1;i <= n;cout << '\n' ,i++) for(j = 1;j <= m;j++)  cout << data[row[i] * m + col[j]] << " ";
	}
}
