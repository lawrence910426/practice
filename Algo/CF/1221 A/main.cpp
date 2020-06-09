#include <iostream>

using namespace std;

int main()
{
    int T ,N;
    int i;
    long long int tmp ,sum;
    for(cin >> T;T--;) {
        cin >> N;
        sum = 0;
        while(N--) {
            cin >> tmp;
            if(tmp <= 2048) sum += tmp;
        }
        if(sum >= 2048) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
