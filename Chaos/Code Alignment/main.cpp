#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
using namespace std;

int leng[185] ,word = 0,line = 0;
string data[185][1005];

int main()
{
	string eax; int i,j ,k;
	for(i = 0;i != 185;i++) for(leng[i] = 0 ,j = 0;j != 1005;j++) data[i][j] = "";
	
	while(getline(cin ,eax)) {
		i = 0;
		stringstream ss(eax);
		while(ss >> data[i++][line]) ;
		word = max(word ,i) ,line++;
	}
	
	
	for(i = 0;i != word;i++) for(j = 0;j != line;j++)
		leng[i] = max(leng[i] ,(int)data[i][j].length() + 1) ;
	for(j = 0;j != line;cout << endl ,j++) for(i = 0;i != word;i++) 
		if(data[i][j] != "")
			for(cout << data[i][j] ,k = (int)data[i][j].length() ;
				k != leng[i] && !(i + 1 == word || data[i + 1][j] == ""); k++) cout << " ";
}
