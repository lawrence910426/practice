#include <iostream>
#include <cstring>
#include <map>
#include <memory>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
struct tree{
	tree *l ,*r;
	char v;
	bool hasl ,hasr;
}data[100];

int used;
map<char ,int> cent ,back;

void build(string cs ,string bs,tree parent)
{
	if(cs.size() == 1)
	{
		used += 1;
		data[used].v = cs[0];
		return;
	}
	char top = bs[bs.size() - 1];
	
	build(substr(0 ,cent[top]) ,substr(0 ,cent[top]) 
}

void show(tree t)
{
	printf("%c" ,t.v);
	if(t.hasl) show(t.l);
	if(t.hasr) show(t.r);
}

int main(int argc, char** argv) {
	int i ,j;
	while(cin >> cs)
	{
		memset(data ,0 ,sizeof(data));
		for(i = 0;i != cs.size();i++) cent[cs[i]] = i;
		for(cin >> bs,i = 0;i != bs.size();i++) back[bs[i]] = i;
		data[0]->v = ' ';
		string cs ,bs;
		build(cs ,bs ,data[0]);
	}
	return 0;
}
