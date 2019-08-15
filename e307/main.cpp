#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main() {
    register char c;
    register bool odd = false;
    while((c = getchar_unlocked()) != EOF) {
        if(c == ' ') odd = !odd;
        else {
            if(odd) putchar_unlocked(' ');
            putchar_unlocked(c);
            odd = false;
        }
    }
}
