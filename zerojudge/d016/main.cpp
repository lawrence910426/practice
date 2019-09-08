#include <iostream>
#include <sstream>
#include <cstring>
#include <stack>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;
int main(int argc, char** argv) {
	stringstream ss;
	string line ,tmp;
	stack<int> stk;
	int a ,b;
	while(getline(cin ,line))
	{
		stringstream ss(line);
		stk = stack<int>();
		while(ss >> tmp) 
		{
			if(tmp == "+") {
				a = stk.top() ,stk.pop();
				b = stk.top() ,stk.pop();
				stk.push(a + b);
			} else if(tmp == "-") {
				b = stk.top() ,stk.pop();
				a = stk.top() ,stk.pop();
				stk.push(a - b);
			} else if(tmp == "*") {
				a = stk.top() ,stk.pop();
				b = stk.top() ,stk.pop();
				stk.push(a * b);
			} else if(tmp == "/") {
				b = stk.top() ,stk.pop();
				a = stk.top() ,stk.pop();
				stk.push(a / b);
			} else if(tmp == "%") {
				b = stk.top() ,stk.pop();
				a = stk.top() ,stk.pop();
				stk.push(a % b);
			} else {
				stk.push(stoi(tmp));
			}
			//cout << stk.top() << endl;
		}
		cout << stk.top() << endl;
	} 
	return 0;
}
