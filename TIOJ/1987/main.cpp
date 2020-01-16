#pragma GCC optimize("Ofast")
#include <iostream>
#include <cmath>
#include <algorithm>
#include "lib1987.h"
using namespace std;
const double pi = acos(-1);
const int MAXN = 3e6 + 50;
struct comp {
    double r ,i;
    comp() {}
    comp(double real ,double imag): r(real) ,i(imag) {}
    comp operator+ (comp b) { return comp(r + b.r ,i + b.i); }
    comp operator- (comp b) { return comp(r - b.r ,i - b.i); }
    comp operator* (comp b) { return comp(r * b.r - i * b.i ,r * b.i + i * b.r); }
    comp operator/ (double b) { return comp(r / b ,i / b); }
};
comp pF[MAXN] ,pG[MAXN] ,pAns[MAXN];
/* assume len = 2^i which i is an integer. */
void rearrange(comp* data ,int siz) {
    int i ,j ,ptr ,len = __lg(siz);
    for(i = 0;i < siz;i++) {
        for(j = ptr = 0;ptr < len;ptr++) j |= ((i >> ptr) & 1) << (len - ptr - 1);
        if(i < j) swap(data[i] ,data[j]);
    }
}
/* type = 1 means DFT ,type = -1 means IDFT */
void FFT(comp* data ,int len ,int type) {
    rearrange(data ,len);
    for(int step = 2;step <= len;step <<= 1) {
        comp radius = comp(cos(-type * 2 * pi / step) ,sin(-type * 2 * pi / step));
        for(int pos = 0;pos < len;pos += step) {
            comp omega = comp(1 ,0);
            for(int ptr = pos;ptr < pos + step / 2;ptr++) {
                comp a = data[ptr] ,b = omega * data[ptr + step / 2];
                data[ptr] = a + b ,data[ptr + step / 2] = a - b;
                omega = omega * radius;
            }
        }
    }
    if(type == -1) for(int i = 0;i < len;i++) data[i] = data[i] / (double)len;
}
void multiply(int N, int M, long long* a, long long* b, long long* ans) {
    int i ,siz;
    for(siz = 1;siz < N + M + 1;siz <<= 1) ;
    for(i = 0;i < siz;i++) pF[i] = comp((i <= N ? a[i] : 0) ,0);
    for(i = 0;i < siz;i++) pG[i] = comp((i <= M ? b[i] : 0) ,0);
    FFT(pF ,siz ,1) ,FFT(pG ,siz ,1);
    //for(i = 0;i < N + M + 1;i++) printf("pF:\t%.2llf\t\t%.2llf\n" ,pF[i].r ,pF[i].i);
    //cout << endl;
    //for(i = 0;i < N + M + 1;i++) printf("pG:\t%.2llf\t\t%.2llf\n" ,pG[i].r ,pG[i].i);
    //cout << endl;
    for(i = 0;i < siz;i++) pAns[i] = pF[i] * pG[i];
    FFT(pAns ,siz ,-1);
    for(i = 0;i < N + M + 1;i++) ans[i] = round(pAns[i].r);
}
