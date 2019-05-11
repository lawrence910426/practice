#include <iostream>
#include <cstring>
#include <stack>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int main(int argc, char** argv) {
	cin.tie(0) ,cout.tie(0) ,ios::sync_with_stdio(0);
	int n ,i ,ans;
	string s;
	stack<char> stk;
	for(cin >> n;n--;)
	{
		cin >> s ,stk = stack<char>() ,ans = 0;
		for(i = 0;i != s.size();i++)
		{
			if(s[i] == '.') continue;
			if(stk.size() == 0) stk.push(s[i]);
			else
				if(s[i] == 'q' && stk.top() == 'p') stk.pop() ,ans++;
				else stk.push(s[i]);	
		}
		cout << ans << endl;
	}	
}
