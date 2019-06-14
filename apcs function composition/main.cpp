#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

int digit(int value) {
    int ret = 0;
    while(value) {
        ret += 1;
        value /= 10;
    }
    return ret;
}

long long pow10(int n) {
    int ret = 1;
    for(;n;n--) ret *= 10;
    return ret;
}

long long int calc() {
    char func; cin >> func;
    if(func == 'f') {
        return 2 * calc() - 3;
    } else if(func == 'g') {
        return 2 * calc() + calc() - 7;
    } else if(func == 'h') {
        return 3 * calc() - 2 * calc() + calc();
    } else if(func == '-') {
        int value; cin >> value;

        //cout << -value << endl;
        return -value;
    } else {
        int peek = cin.peek();
        if('0' <= peek && peek <= '9') {
            cin >> peek;

            //cout << (func - '0') * pow10(digit(peek)) + peek << endl;
            return (func - '0') * pow10(digit(peek)) + peek;
        } else {

            //cout << (func - '0') << endl;
            return (func - '0');
        }
    }
}

int main() {
    string data;
    while(!cin.eof()) {
        cout << calc() << endl;
    }
}
