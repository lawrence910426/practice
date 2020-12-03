#include <iostream>
#include <cstring>
#include <memory.h>
#include <algorithm>

using namespace std;

const int MAXN = 5e3 + 10;

class BigInt {
	int storage[MAXN];
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
	BigInt(const BigInt& clone) { memcpy(storage, clone.storage, sizeof(storage)); }
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
	memset(item.storage, 0, sizeof(item.storage));
	string s;
	is >> s;
	bool neg = (s[0] == '-');
	reverse(s.begin() + (neg ? 1 : 0), s.end());
	for(int i = (neg ? 1 : 0);i < s.size();i++) item.storage[i - (neg ? 1 : 0)] = s[i] - '0';
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
