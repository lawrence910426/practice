#include <iostream>
#include <stack>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main() {
	long long int ans ,n;		int eax;
	while(cin >> n)
	{
		stack<int> house; ans = 0;
		while(n--)
		{
			cin >> eax;
			if(house.empty()) 
				house.push(eax);
			else if(house.top() >= eax) 
				ans += house.size() ,house.push(eax);
			else
			{
				ans += house.size();
				while(!house.empty() && house.top() < eax) house.pop();
				house.push(eax);
			}
		}
		cout << ans * 2 << endl;
	}
}
