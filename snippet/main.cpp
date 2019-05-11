#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main(int argc, char** argv) {
	int i ,j;
	for(i = 0;i != 256;i++) for(j = 0;j != 256;j++)
		cout << "<domain includeSubdomains=\"true\">192.168." << i << "." << j << "</domain>" << endl;
	return 0;
}
