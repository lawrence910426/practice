#include <iostream>

using namespace std;

int N ,b;

inline int adapt() {
    int times = 1, result = 0 ,tmp = N;
    while(tmp) {
        result += (tmp % 10) * times;
        times *= b;
        tmp /= 10;
    }
    return result;
}

inline int pow(int base, int power) {
    int ret = 1;
    //cout << base << " " << power << " " << ret << endl;
    while(power--) ret *= base;

    return ret;
}

inline int sum() {
    int sum = 0, tmp = N ,digit = 0;
    while(tmp) digit += 1, tmp /= 10;
    for(tmp = N;tmp;tmp /= 10) sum += pow(tmp % 10 ,digit);
    return sum;
}

int main() {
    while(cin >> b >> N) {
        //cout << sum() << " " << adapt() << endl;
        cout << (sum() == adapt() ? "YES" : "NO") << endl;
    }
}
