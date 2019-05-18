#include <iostream>
#include <cstring>
#define INF (1LL << 31 - 1)
using namespace std;

long long int gcd(long long int x ,long long int y) { return (x % y == 0 ? y : gcd(y ,x % y)); }

int main() {
	int N, data[100] ,share ,length;
	int i;
	long long int best_up ,best_down ,up ,down;
	string line;
	while(getline(cin ,line) ,line.find('.') != std::string::npos) {
		for(length = 0 ,i = 0;i < line.size();i++) {
			if(line[i] == '.' && length == 0) length += 1;
			else if(line[i] != '.' && length != 0) data[length - 1] = line[i] - '0' ,length += 1;
			else if(line[i] == '.' && length != 0) break;
		}
		length -= 1;
		
		best_up = best_down = INF;
		for(N = 1;N <= length;N++) {
			for(down = 9 ,i = 0;i < N - 1;i++) down = down * 10 + 9;
			for(i = 0;i < length - N;i++) down *= 10;
			for(up = i = 0;i < length;i++) {
				if(i >= N) up = up * 10 + data[i] - data[i - N];
				else up = up * 10 + data[i];
			}
			share = gcd(up ,down);
			down /= share ,up /= share;
			//printf("%lld/%lld\n" ,up ,down);
			if(down < best_down) best_up = up ,best_down = down;
		}
		printf("%lld/%lld\n" ,best_up ,best_down);
	}
}
