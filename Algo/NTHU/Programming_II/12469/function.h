#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 5e3 + 10;

class BigInt {
	vector<int> storage = vector<int>(MAXN, 0);
	void Inverse() {
		int remain = 10;
		for(int i = 0;i < MAXN;i++) {
			storage[i] = remain - storage[i];
			remain = (storage[i] >= 10 ? 10 : 9);
			storage[i] %= 10;
		}
	}
	static bool is_number(char c) { return '0' <= c && c <= '9'; }
public:
	BigInt() { }
	BigInt(const BigInt& clone) { storage = vector<int>(clone.storage); }
	friend istream& operator >> (istream&, BigInt&);
	friend ostream& operator << (ostream&, BigInt);	
	BigInt operator + (const BigInt&);
	BigInt operator - (const BigInt&);
};

BigInt BigInt::operator + (const BigInt& item) {
	BigInt ans(item);
	bool carry = false;
	for(int i = 0;i < MAXN;i++) {
		ans.storage[i] += this->storage[i] + (carry ? 1 : 0);
		carry = ans.storage[i] >= 10;
		ans.storage[i] %= 10;
	}
	return ans;
}

BigInt BigInt::operator - (const BigInt& item) {
	BigInt ans(item);
	ans.Inverse();
	return *this + ans;
}

istream& operator >> (istream& is, BigInt& item) {
	item.storage = vector<int>(MAXN, 0);
	char temp = '\0';
	if(!is.eof() && !BigInt::is_number(is.peek())) is.get(temp);
	bool neg = (temp == '-');
	int N = 0;
	while(is.get(temp) && BigInt::is_number(temp)) item.storage[N++] = temp - '0';
	reverse(item.storage.begin(), item.storage.begin() + N);
	if(neg) item.Inverse();
	return is;
}

ostream& operator << (ostream& os, BigInt item) {
	if(item.storage[MAXN - 1] != 0) { item.Inverse(); os << '-'; }
	int N = MAXN - 2;
	while(N >= 0 && item.storage[N] == 0) N -= 1;
	while(N >= 0) os << item.storage[N--];
	return os;
}
