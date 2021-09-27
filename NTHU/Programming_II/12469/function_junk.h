#include<iostream>
#include<algorithm>
#include<string> 
using namespace std; 
#define MAX_N 1000
#define MAX_Bit 5
#define MAX 100000

class BigInt{
private:
	long long storage[MAX_N];
	int length;
public:
	long long operator [](int i) const { return storage[i]; }
	long long &operator [](int i) { return storage[i]; }
	BigInt() { length=1; storage[0]=0; }
	BigInt(int x) { (*this)=x; }
	BigInt(const char *s) { (*this)=s; }
	BigInt(const BigInt& clone): length(clone.length) { copy(clone.storage, clone.storage + length, storage); }
	void Inverse() {
		int remain = 10;
		for(int i = 0;i < MAX_N;i++) {
			storage[i] = remain - storage[i];
			remain = 9;
			if(storage[i] == 10) { storage[i] = 0; remain += 1; }
		}
	}
        friend istream& operator>>(istream& is, BigInt& item) {
		char temp;
		if('0' <= is.peek() && is.peek() <= '9') is >> temp;
		bool neg = (temp == '-');
		item.length = 0;
		for(is >> temp;'0' <= temp && temp <= '9';is >> temp) item.storage[item.length++] = temp - '0';
		if(neg) item.Inverse();
		return is;
	}
        friend ostream& operator<<(ostream& os, BigInt item) {
		for(int i = item.length - 1;i >= 0;i--) os << item.storage[i];
		return os;
	}
        BigInt operator +( const BigInt &y ) {
		BigInt ans(*this);
		bool carry = false;
		for(int i = 0;i < MAX_N;i++) {
			ans.storage[i] += y.storage[i] + (carry ? 1 : 0);
			if(ans.storage[i] >= 10) {
				carry = true;
				ans.storage[i] -= 10;
			} else carry = false;
		}
		return ans;
	}
        BigInt operator -( const BigInt &y ) {
		BigInt ans(y);
		ans.Inverse();
		return *this + y;
	}
};

