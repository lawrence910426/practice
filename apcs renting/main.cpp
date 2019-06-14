#include <iostream>
#include <map>
using namespace std;

map<int ,bool> dp ,tmp;
int main()
{
    int n ,M ,S ,sum;
    int i ,value;
    map<int ,bool>::iterator iter;
    while(cin >> n >> M >> S) {
        M -= S;
        dp = map<int ,bool>();
        for(sum = i = 0;i < n;i++) {
            cin >> value;

            tmp = map<int, bool>();
            for(iter = dp.begin();iter != dp.end();iter++) {
                tmp[iter->first + value] = true;
            }
            tmp[value] = true;
            for(iter = tmp.begin();iter != tmp.end();iter++) {
                dp[iter->first] = true;
            }

            /*cout << endl;
            for(iter = dp.begin();iter != dp.end();iter++)
                cout << iter->first << endl;*/

            sum += value;
        }

        for(i = M;i >= 0;i--)
            if(dp[i]) break;
        cout << sum - i << endl;
    }
}

/*
3 10 6
4 4 1

5 20 14
8 2 7 2 1
*/

/*
discriminate style of dp
*/
