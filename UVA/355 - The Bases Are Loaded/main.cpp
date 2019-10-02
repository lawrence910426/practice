#include <iostream>
#include <cstring>
using namespace std;
string origin_value ,target_value;
int origin_base ,target_base;
inline char itoc(int i) { return (i >= 10 ? i - 10 + 'A' : i + '0'); }
int main() {
    int i;
    long long int value ,pow;
    while(cin >> origin_base >> target_base >> origin_value) {
        value = 0 ,pow = 1;
        for(i = origin_value.size() - 1;i >= 0;i--) {
            char c = origin_value[i];
            if(origin_base <= 10) {
                if('0' <= c && c <= '0' + origin_base - 1) value += (c - '0') * pow;
                else break;
            } else {
                if('0' <= c && c <= '9') value += (c - '0') * pow;
                else if('A' <= c && c <= 'A' + origin_base - 11) value += (c - 'A' + 10) * pow;
                else break;
            }
            pow *= origin_base;
        }
        if(i == -1) {
            if(value == 0) target_value = "0";
            else for(target_value = "";value > 0;value /= target_base) target_value = itoc(value % target_base) + target_value;
            cout << origin_value << " base " << origin_base << " = " << target_value << " base " << target_base << endl;
        } else cout << origin_value << " is an illegal base " << origin_base << " number" << endl;
    }
}
/*
2 10 10101
5 3 126
15 11 A4C
*/
