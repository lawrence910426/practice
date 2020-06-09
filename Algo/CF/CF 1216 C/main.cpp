#include <iostream>
#define pos(a) ((a) > 0 ? (a) : 0)
#define wb pos(min(wx2 ,bx2) - max(wx1 ,bx1)) * pos(min(wy2 ,by2) - max(wy1 ,by1))
#define wbb pos(min(wx2 ,bbx2) - max(wx1 ,bbx1)) * pos(min(wy2 ,bby2) - max(wy1 ,bby1))
#define bbb pos(min(bx2 ,bbx2) - max(bx1 ,bbx1)) * pos(min(by2 ,bby2) - max(by1 ,bby1))


using namespace std;

int main()
{
    long long int wx1 ,wx2 ,wy1 ,wy2 ,space;
    long long int bx1 ,bx2 ,by1 ,by2;
    long long int bbx1 ,bbx2 ,bby1 ,bby2;
    cin >> wx1 >> wy1 >> wx2 >> wy2;
    cin >> bx1 >> by1 >> bx2 >> by2;
    cin >> bbx1 >> bby1 >> bbx2 >> bby2;
    space = (wy2 - wy1) * (wx2 - wx1); //cout << space << endl;
    space -= pos(wb); //cout << pos(wb) << endl;
    space -= pos(wbb); //cout << pos(wbb) << endl;
    space += pos(bbb); //cout << pos(bbb) << endl;
    cout << (space == 0 ? "NO" : "YES") << endl;
}
