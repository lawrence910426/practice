#include <iostream>
#include <sstream>
#include <cstring>
#include <bitset>

using namespace std;

int main()
{
    string line;
    int tmp ,sum;
    while(getline(cin ,line)) {
        stringstream ss = stringstream(line);
        bitset<1000> dp; sum = 0;
        while(ss >> tmp) {
            sum += tmp;
            dp |= dp << tmp;
            dp[tmp] = true;
        }
        if(sum % 2 == 1) cout << "NO" << endl;
        else {
            cout << (dp[sum / 2] ? "YES" : "NO") << endl;
        }
    }
}
