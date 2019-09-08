#include <iostream>
#define abs(a) ((a) > 0 ? (a) : -(a))
using namespace std;
#define N 100000
int data[N] ,pprefix[N] ,ssuffix[N];
int M ,H;

int divide(int l ,int r ,int depth) {
    if(r - l < 3) return 0;
    if(depth >= H) return 0;

    int i;
    pprefix[l] = data[l] ,ssuffix[r - 1] = data[r - 1];
    for(i = l + 1;i < r;i++) pprefix[i] = pprefix[i - 1] + data[i];
    for(i = r - 2;i >= l;i--) ssuffix[i] = ssuffix[i + 1] + data[i];

    for(i = l + 1;i < r;i++) pprefix[i] = pprefix[i - 1] + pprefix[i];
    for(i = r - 2;i >= l;i--) ssuffix[i] = ssuffix[i + 1] + ssuffix[i];

    int ptr ,best_v = (1LL << 31) - 1 ,best_i = -1;
    for(ptr = l + 1;ptr < r - 1;ptr++) {
        if(abs(pprefix[ptr - 1] - ssuffix[ptr + 1]) < best_v) {
            best_i = ptr;
            best_v = abs(pprefix[ptr - 1] - ssuffix[ptr + 1]);
        }
    }
    return divide(l ,best_i ,depth + 1) + data[best_i] + divide(best_i + 1 ,r ,depth + 1);
}

int main()
{
    int i ,eax ,ebx;
    while(cin >> M >> H) {
        for(i = 0;i < M;i++) cin >> data[i];
        //cin >> eax >> ebx;
        cout << divide(0 ,M ,0) << endl;
    }
    return 0;
}

/*
Fuck you ,i spent a lot of time on it.
This code will work(?) ,i guess so
*/
