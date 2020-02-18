#include <iostream>
#include <random>
using namespace std;
const int CATS = 3e5 ,MEOW = 65536 ,TIMES = 1e3;
int X[CATS] ,Y[CATS] ,chosen[MEOW] ,mirror[MEOW];
int get(int i) { return (mirror[i] == i ? i : mirror[i] = get(mirror[i])); }
int main() {
    int i;
    for(i = 0;i < CATS;i++) cin >> X[i] >> Y[i];
    for(i = 0;i < MEOW;i++)
    for(i = 0;i < MEOW;i++)
    for(int times = 0;times < TIMES;i++) {

    }
}
