#include <iostream>
#include <cstring>

using namespace std;
int get_best(string a ,string b) {
    int best = (1LL << 31) - 1 ,i ,shift ,value ,asiz = a.size() ,bsiz = b.size();
    char ca ,cb;
    for(shift = -asiz;shift < bsiz;shift++) {
        value = 0;
        for(i = min(-shift ,0);i < max(asiz - shift ,bsiz);i++) {
            ca = (0 <= i + shift && i + shift < asiz ? a[i + shift] : 0);
            cb = (0 <= i && i < bsiz ? b[i] : 0);
            if(ca == 0 && cb == 0) value += 0;
            else if(ca == 0 && cb != 0) value += 2;
            else if(ca != 0 && cb == 0) value += 2;
            else if(ca != cb) value += 3;
        }
        best = min(best ,value);
    }
    return best;
}

int main() {
    string raw ,a ,b, c;
    int K[3] ,best ,i ,tmp;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> raw >> a >> b >> c) {
        K[0] = get_best(raw ,a);
        K[1] = get_best(raw ,b);
        K[2] = get_best(raw ,c);
        best = 2;
        for(i = 1;i >= 0;i--) if(K[best] > K[i]) best = i;
        cout << best + 1 << " " << K[best] << endl;
    }
}
