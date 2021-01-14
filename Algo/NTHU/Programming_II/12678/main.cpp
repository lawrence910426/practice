#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long power[10];

vector<int> digit = vector<int>(10);
long long amount(long long x) {
	int size = 0;
	for(int temp = x;temp > 0;temp /= 10) digit[size++] = temp % 10;
	reverse(digit.begin(), digit.begin() + size);
	
	long long ans = 0, ones = 0;
	for(int i = 0;i < size;i++) {
		for(int value = 0;value < digit[i];value += 1) {
			int N = size - 1 - i;
			ans += N * power[N - 1];
			ans += (ones + (value == 1 ? 1 : 0)) * power[N];
		}
		ones += (digit[i] == 1 ? 1 : 0);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	power[0] = 1;
	for(int i = 1;i < 10;i++) power[i] = power[i - 1] * 10;

	int T;
	long long l, r;
	for(cin >> T;T--;) {
		cin >> l >> r;
		cout << amount(r + 1) - amount(l) << '\n';	
	}
}
