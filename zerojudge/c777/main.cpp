#include <iostream>
#include <cstring>
#define min(a ,b) (a > b ? b : a)
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

string add(string a ,string b) //a > b
{
	a = '0' + a;
	int i ,j ,value;
	for(i = 0;i != b.size();i++)
	{
		value = a[a.size() - 1 - i] + b[b.size() - 1 - i] - '0' - '0';
		if(value >= 10) {
			a[a.size() - 1 - i] = value - 10 + '0';
			for(j = i + 1;j < a.size();j++) 
				if(a[a.size() - 1 - j] == '9') a[a.size() - 1 - j] = '0';
				else {
					a[a.size() - 1 - j] += 1;
					break;
				}
		}
		else a[a.size() - 1 - i] = value + '0';
	}
	if(a[0] == '0') return a.erase(0 ,1);
	else return a;
}

bool bigger(string a ,string b) //a > b
{
	if(a.size() > b.size()) return true;
	if(a.size() < b.size()) return false;
	for(int i = 0;i != a.size();i++) 
		if(a[i] > b[i]) return true;
		else if(a[i] < b[i]) return false;
	//totally equal
	return true;
}

int main(int argc, char** argv) {
	string a ,b ,c ,d ,n ,m;
	int ans;
	while(cin >> n >> m) {
		ans = 0;
		a = "0" ,b = "1" ,c = "2" ,d = "3";
		if(n == a) n = d, ans += 3;
		else if(n == b) n = d, ans += 2;
		else if(n == c) n = d, ans += 1;
		
		while(bigger(m ,d)) {
			d = add(a ,add(b ,c));
			if((n == d || bigger(d ,n)) && (m == d || bigger(m ,d)))
			{
				//cout << "found:" << d << endl;
				ans += 1;	
			} 
			a = b ,b = c ,c = d;
			//cout << d << endl;
		}
		cout << ans << endl;
	}
}
