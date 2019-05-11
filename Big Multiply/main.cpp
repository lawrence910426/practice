#include <iostream>
#include <cstring>

using namespace std;

inline string add(string X ,string Y) {
	if(X.size() < Y.size()) {
		string tmp = X;
		X = Y;
		Y = tmp;
	}

	//X > Y
	int i ,j;
	for(i = 0;i < Y.size();i++) {
		if(X[X.size() - i - 1] + Y[Y.size() - i - 1] - '0' - '0' >= 10) {
			X[X.size() - i - 1] += Y[Y.size() - i - 1] - '0' - 10;
			for(j = i + 1;j < X.size();j++) 
				if(X[X.size() - j - 1] == '9') X[X.size() - j - 1] = '0';
				else {
					X[X.size() - j - 1] += 1;
					break;	
				}
			if(j == X.size()) X = '1' + X;
		} else X[X.size() - i - 1] += Y[Y.size() - i - 1] - '0';
	}
	return X;
}

inline string tostring(int i) {
	string ret;
	if(i >= 10) {
		ret = "00";
		ret[0] = i / 10 + '0';
		ret[1] = i % 10 + '0';
	} else {
		ret = "0";
		ret[0] = i + '0';
	}
	return ret;
}

string mul[1000][1000] ,sum[1000];
int main() {
	string X ,Y ,ret;
	int i ,j ,k ,tmp;
	
	ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
	while(cin >> X >> Y) {
		if(X == "0" || Y == "0") {
			cout << "0" << endl;
			continue;
		}
		
		for(i = 0;i < X.size();i++) for(j = 0;j < Y.size();j++) {
			tmp = (X[i] - '0') * (Y[j] - '0');
			mul[i][j] = tostring(tmp);
		}
		
		for(i = 0;i <= X.size() + Y.size();i++) sum[i] = "0";
		for(i = 0;i < X.size();i++) for(j = 0;j < Y.size();j++) 
			sum[i + j] = add(sum[i + j] ,mul[i][j]);
			
		ret = "0";
		/*for(i = 0;i < X.size();cout << endl ,i++) for(j = 0;j < Y.size();j++) 
			cout << mul[i][j] << " ";
		cout << endl;*/
		for(i = 0;i < X.size() + Y.size() - 1;i++) {
			//cout << sum[i] << endl;
			for(j = 0;j < X.size() + Y.size() - 2 - i;j++)
				sum[i] = sum[i] + "0";
			ret = add(ret ,sum[i]);
		}
		cout << ret << endl;
	}
}

/*
123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790123456790
*/
