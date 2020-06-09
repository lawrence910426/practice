#include <iostream>

using namespace std;

int main()
{
    int l ,r ,d;
    for(cin >> l >> r >> d ;l != r;l += d) cout << l << " ";
    cout << r << endl;
}
