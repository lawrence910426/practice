#include <iostream>
#include <cstring>
#pragma GCC optimize ("O3")

using namespace std;


inline string add(string a ,string b){
	register int i ,j ,value ,sizea = a.size() ,sizeb = b.size();
	if(sizea < sizeb) {
		string tmp = a;
		a = b;
		b = tmp;
		
		sizea ^= sizeb;
		sizeb ^= sizea;
		sizea ^= sizeb;
	}

	for(i = 0;i < sizeb;i++) {
		value = b[sizeb - i - 1] + a[sizea - i - 1] - '0' - '0';
		if(value >= 10) {
			a[sizea - i - 1] = value - 10 + '0';
			for(j = i + 1;j < sizea;j++) 
				if(a[sizea - j - 1] == '9') a[sizea - j - 1] = '0';
				else {
					a[sizea - j - 1] += 1;
					break;
				}
			if(j == sizea) a = '1' + a;
		} else a[sizea - i - 1] = value + '0';
	}
	return a;
}

short summed[6000];
inline string mul(string a ,string b) {
	register int i ,j;
	for(i = 0;i < a.size() + b.size();i++) summed[i] = 0;
	for(i = 0;i < a.size();i++) for(j = 0;j < b.size();j++)
		summed[i + j] += (a[i] - '0') * (b[j] - '0');
	
	string ret = "0" ,zeros = "";
	for(i = a.size() + b.size() - 2;i >= 0;i--)  {
		ret = add(to_string(summed[i]) + zeros ,ret);
		zeros += "0";
	}
	return ret;
}

int digit_sum(string s) {
	int i = 0 ,ret = 0;
	for(i = 0;i < s.size();i++) ret += s[i] - '0';
	return ret;
}

int main() {
	string tmp = "1" ,ans[1005];
	register int N;
	register int i;
	
	ans[0] = 1;
	for(i = 1;i < 1005;i++) {
		tmp = mul(tmp ,to_string(i));
		ans[i] = tmp; 
		//cout << tmp.size() << " ";
	}
	
	while(cin >> N) cout << digit_sum(ans[N]) << endl;
	
}
