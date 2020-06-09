#include <iostream>
#include <map>
#include <cstring>

using namespace std;
map<string, string> S;
int main() {
    S["!!"] = 'V';
    S["!@"] = '5';
    S["!#"] = 'I';
    S["!$"] = 'K';
    S["!%"] = 'E';
    S["!&"] = 'U';

    S["@!"] = 'F';
    S["@@"] = '0';
    S["@#"] = 'W';
    S["@$"] = 'G';
    S["@%"] = '3';
    S["@&"] = 'Z';

    S["#!"] = 'Y';
    S["#@"] = 'M';
    S["##"] = 'H';
    S["#$"] = 'B';
    S["#%"] = 'C';
    S["#&"] = '8';

    S["$!"] = 'J';
    S["$@"] = '2';
    S["$#"] = 'S';
    S["$$"] = 'X';
    S["$%"] = '7';
    S["$&"] = 'R';

    S["%!"] = '6';
    S["%@"] = '9';
    S["%#"] = '4';
    S["%$"] = 'T';
    S["%%"] = 'P';
    S["%&"] = 'D';

    S["&!"] = '1';
    S["&@"] = 'L';
    S["&#"] = 'Q';
    S["&$"] = 'A';
    S["&%"] = 'N';
    S["&&"] = 'O';

    string item;
    while(cin >> item, item != "FUCK") {
        if(S.find(item) == S.end()) cout << item;
        else cout << S[item];
    }
}
