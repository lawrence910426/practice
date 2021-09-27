#include <iostream>
#include <cstring>
#include <memory.h>
#include <algorithm>
#include <stack>
#include <cmath>

using namespace std;

const int MAXN = 650, SYS = 1e8;

class BigInt {
	int storage[MAXN];
	void Inverse() {
		int remain = SYS;
		for(int i = 0;i < MAXN;i++) {
			storage[i] = remain - storage[i];
			remain = (storage[i] >= SYS ? SYS : SYS - 1);
			storage[i] %= SYS;
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

stack<BigInt*> waste;

BigInt BigInt::operator + (const BigInt& item) {
    BigInt *ans = new BigInt(*this);
    waste.push(ans);
    bool carry = false;
	for(int i = 0;i < MAXN;i++) {
		ans->storage[i] += item.storage[i] + (carry ? 1 : 0);
		carry = ans->storage[i] >= SYS;
		ans->storage[i] %= SYS;
	}
    return *ans;
}

BigInt BigInt::operator - (const BigInt& item) {
	BigInt *ans = new BigInt(item);
    waste.push(ans);
    ans->Inverse();
    return *this + *ans;
}

istream& operator >> (istream& is, BigInt& item) {
    for(;!waste.empty();waste.pop()) delete waste.top();
	memset(item.storage, 0, sizeof(item.storage));
	string s;
	is >> s;
	bool neg = (s[0] == '-');
	reverse(s.begin() + (neg ? 1 : 0), s.end());
	int i = (neg ? 1 : 0);
    while(i < s.size()) {
        int j = 0, pow = 1;
        while(pow < SYS && i + j < s.size()) {
            item.storage[i - (neg ? 1 : 0)] += (s[i + j] - '0') * pow;
            pow *= 10;
            j += 1;
        }
        i += 8;
    }
    if(neg) item.Inverse();
	return is;
}

ostream& operator << (ostream& os, BigInt item) {
	if(item.storage[MAXN - 1] != 0) { item.Inverse(); os << '-'; }
	int N = MAXN - 2;
	while(N >= 0 && item.storage[N] == 0) N -= 1;
	while(N >= 0) os << (int)item.storage[N--];
    return os;
}
