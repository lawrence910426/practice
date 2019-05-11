#include <iostream>
#include <cstring>
#include <memory.h>

using namespace std;

string data[185][1005];
int leng[185];

int main()
{
	register char eax;
	int word = 0 ,line = 0				,i ,j ,k;
	while(memset(data ,0, sizeof(data)) ,memset(leng ,0 ,sizeof(leng))
		,scanf("%c" ,&eax) != EOF)
	{
		if(eax == '\n') line++;
		else if(eax == ' ')
			if(data[word][line] == "") continue;
			else word++;
		else data[word][line] += eax;
	}

	for(i = 0;i != word;i++) for(j = 0;j != line;j++)
		printf("%d" ,data[i][j].size());
	
	for(i = 0;i != word;printf("\n") ,i++) for(j = 0;j != line;j++)
	{
		cout << data[i][j];
		if(!(i + 1 == word && data[i + 1][j] == ""))
			for(k = 0;k != leng[i]; printf("%d" ,data[i][j].size()))
				cout << ' ';
	}
	
}
