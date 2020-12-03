#include<iostream>
#include<algorithm>
#include<string> 
#include<memory.h>
using namespace std; 
#define MAX_N 1000
#define MAX_Bit 5
#define MAX 100000
class BigInt{
        static void Add(long long* ans, int* lans, const long long* a, const long long *b ,const int la, const int lb) {
            for(*lans = 0;*lans < la || *lans < lb;*lans += 1) {
                ans[*lans] += a[*lans] + b[*lans];
                ans[*lans + 1] += ans[*lans] / MAX;
                ans[*lans] %= MAX;
            }
            if(ans[*lans] == 0) *lans -= 1;
        }
        static void Sub(long long* ans, int* lans, const long long* a, const long long *b, const int la, const int lb) {
            for(*lans = 0;*lans < la;*lans += 1) {
                ans[*lans] += a[*lans] - b[*lans];
                if(ans[*lans] < 0) {
                    ans[*lans + 1] -= 1;
                    ans[*lans] += MAX;
                }
            }
            while(ans[*lans] == 0) *lans -= 1;
        }
        static int Compare(long long* a, long long* b, int la, int lb) {
            if(la < lb) return -1;
            if(la > lb) return 1;
            for(int i = la - 1;i >= 0;i--) {
                if(a[i] > b[i]) return 1;
                if(a[i] < b[i]) return -1;
            }
            return 0;
        }
	public:
		int sign;
		long long m[MAX_N];
		int l;
		long long operator [](int i) const { return m[i]; }
		long long &operator [](int i) { return m[i]; }
		BigInt(){ l=1, m[0]=0; sign=1; }
		BigInt(int x){ (*this)=x; }
		BigInt(const char *s){ (*this)=s; }
        friend istream& operator>>(istream&, BigInt&);   
        friend ostream& operator<<(ostream&, BigInt);   
        BigInt operator +( const BigInt &y );  
        BigInt operator -( const BigInt &y );      
};

istream& operator >> (istream& is, BigInt& item) {
    memset(item.m, 0, sizeof(item.m));
    string s;
    is >> s;
    int i = 0, pow = 1;
    item.sign = (s[i] == '-' ? -1 : 1);
    if(s[i] == '-') i += 1;
    reverse(s.begin() + i, s.end());
    for(item.l = 0;i < s.size();i++) {
        item.m[item.l / MAX_Bit] += (s[i] - '0') * pow;
        pow *= 10;
        item.l += 1;
        if(item.l % MAX_Bit == 0) pow = 1;
    }
    item.l = (item.l - 1) / MAX_Bit + 1;
    return is;
}

ostream& operator << (ostream& os, BigInt item) {
    if(item.sign == -1) os << "-";
    int i = item.l;
    while(item[i] == 0 && i >= 0) i -= 1;
    bool flag = true;
    while(i >= 0) {
        if(flag) {
            flag = false;
        } else { 
            os.fill('0');
            os.width(MAX_Bit);
        }
        os << item[i];
        i -= 1;
    }
    return os;
}

BigInt BigInt::operator + (const BigInt &y) {
    /* for(int i = 0;i < 10;i++) cout << m[i] << " ";
    cout << endl;
    for(int i = 0;i < 10;i++) cout << y[i] << " ";
    cout << endl;
    cout << l << " " << y.l << endl;i */
        
    BigInt ans;
    memset(ans.m, 0, sizeof(ans.m));
    if(sign == 1 && y.sign == 1) {
        ans.sign = 1;
        BigInt::Add(ans.m, &ans.l, m, y.m, l, y.l);
    } else if(sign == -1 && y.sign == -1) {
        ans.sign = -1;
        BigInt::Add(ans.m, &ans.l, m, y.m, l, y.l);
    } else {
        ans.sign = sign;
        BigInt a, b;
        memcpy(a.m, this->m, sizeof(this->m));
        a.l = l;
        memcpy(b.m, y.m, sizeof(y.m));
        b.l = y.l;
        if(BigInt::Compare(a.m, b.m, a.l, b.l) == -1) {
            swap(a, b);
            ans.sign = -ans.sign;
        }
        BigInt::Sub(ans.m, &ans.l, a.m, b.m, a.l, b.l);
    }
    return ans;
}

BigInt BigInt::operator - (const BigInt &y) {
    BigInt temp;
    temp.sign = -y.sign;
    temp.l = y.l;
    memcpy(temp.m, y.m, sizeof(y.m));
    return *this + temp;
}

