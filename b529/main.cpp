#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
string cmd ,path;

vector<string> split()
{
	string tmp = ""; vector<string> ret = vector<string>();
	for(int i = 0;i != path.length();i++)
		if(path[i] == '\\') ret.push_back(tmp) ,tmp = "\\";
		else tmp += path[i];
	ret.push_back(tmp);
	return ret;
}

string simple()
{
	vector<string> loc = split();
	string new_path = "";
	restart:
	for(int i = 0;i != loc.size();i++)
		if(loc[i] == "\\_") 
		{
			loc.erase(loc.begin() + i);
			loc.erase(loc.begin() + i - 1);
			goto restart;
		}
	for(int i = 0;i != loc.size();i++)
		new_path += loc[i];
	path = new_path;
	return path;
} 

int main(int argc, char** argv) {
	int t; cin >> t; path = "\\"; t += 1;
	while(t--)
	{
		getline(cin ,cmd);
		if(cmd == "Where's my asphalt?") 
			cout << simple() << endl;
		if(cmd == "Fly away.") 
		{
			getline(cin ,cmd);
			if(cmd[0] == '\\') path = cmd + "\\";
			else path += cmd + "\\";
		}
	}
}
