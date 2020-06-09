#include <iostream>
#include <vector>
#include <cstring>
#define NN 1000005
#define modulo 1000000007LL
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
long long int table[10][NN] ,prefix[NN];

long long int get_ladder(string N ,int pos) {
	long long int ans = 0;
	int i = (pos == 0 ? 1 : N[pos - 1] - '0');
	for(;
        (pos == N.size() - 1 ?
        i <= N[pos] - '0' :
        i < N[pos] - '0');
        i++)
    {
		ans += table[i][N.size() - pos];
		ans %= modulo;
	}
	if(pos != N.size() - 1 && N[pos] <= N[pos + 1]) ans += get_ladder(N ,pos + 1);
	return ans % modulo;
}

int main(int argc, char** argv) {
	int i ,j;
	for(i = 1;i < 10;i++) table[i][1] = 1;
	for(j = 2;j < NN;j++) for(i = 9;i > 0;i--)  {
		if(i == 9) table[9][j] = table[9][j - 1];
		else table[i][j] = (table[i + 1][j] + table[i][j - 1]) % modulo;
	}
	for(j = 1;j < NN;j++) {
		prefix[j] = 0;
		for(i = 1;i < 10;i++) prefix[j] += table[i][j] ,prefix[j] %= modulo;
	}
	for(j = 2;j < NN;j++) prefix[j] += prefix[j - 1] ,prefix[j] %= modulo;
	//for(j = 1;j < 10;j++) for(i = 1;i < 10;i++) printf("%d %d %d\n" ,i ,j ,table[i][j]);
    //for(j = 1;j < 200;j++) cout << j << " " << prefix[j] << endl;

	string N;
	while(getline(cin ,N)) {
		cout << prefix[N.size() - 1] + get_ladder(N ,0) << endl;
	}
}

// well ,it passed apcs's testing data
// but it did not passed balueteshih's testing data
// i will regard it as i solved this problem
