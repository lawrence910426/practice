#include <iostream>
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

string S;
int failure[1000005];

int main() {
	int length;
	int i ,j;
	while(getline(cin ,S) ,S != ".") {
		memset(failure ,-1 ,sizeof(failure));
		for(i = 1;i < S.size();i++) {
			j = failure[i - 1];
			while(j >= 0 && S[j + 1] != S[i]) j = failure[j];
			if(S[j + 1] == S[i]) failure[i] = j + 1;
		}
		
		//for(i = 0;i < S.size();i++) cout << S[i] << "\t\t" << failure[i] << endl;
		
		length = S.size() - 1 - failure[S.size() - 1];
		
		if(S.size() % length == 0) cout << S.size() / length << endl;
		else cout << 1 << endl;
	}
}
