#include <iostream>

using namespace std;

int main()
{
    int n ,l ,r ,ans ,start;
    while(cin >> n ,n) {
        ans = 0 ,start = 1 ,l = 1;
        while(start < n) {
            r = n;
            while(l < r) {
                #define center ((l + r) / 2)
                if(n / center > start) r = center;
                else l = center;
            }
            ans += (r - start) * ()
        }
    }
}
