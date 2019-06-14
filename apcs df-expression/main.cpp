#include <iostream>
#include <cstring>
using namespace std;

int calc(string data ,int* iter ,int imgsize ,int depth) {
    if(data[*iter] == '0') {
        *iter += 1;
        return 0;
    } else if(data[*iter] == '1') {
        *iter += 1;
        return (imgsize / (1 << depth)) * (imgsize / (1 << depth));
    } else if(data[*iter] == '2') {
        *iter += 1;
        int ans = 0;
        ans += calc(data ,iter ,imgsize ,depth + 1);
        ans += calc(data ,iter ,imgsize ,depth + 1);
        ans += calc(data ,iter ,imgsize ,depth + 1);
        ans += calc(data ,iter ,imgsize ,depth + 1);
        return ans;
    }
}

int main()
{
    string data;
    int imgsize ,iter;
    while(cin >> data) {
        cin >> imgsize;
        iter = 0;
        cout << calc(data ,&iter ,imgsize ,0) << endl;
    }
    return 0;
}
/*
2200101020110
4
2020020100010
8
*/
