#include <stdio.h>
#include <string.h>
#include <memory.h>

char str[1000];
int pairing[1000], pos = 0;

long long Eval(int l, int r) {
    int i;
    long long val = 0, temp = 1;
    if(pairing[r - 1] == -1) {
        for(i = r - 1;i >= l && '0' <= str[i] && str[i] <= '9';i--) {
            val += temp * (str[i] - '0');
            temp *= 10;
        }
    } else {
        val = Eval(pairing[r - 1] + 1, r - 1);
        i = pairing[r - 1] - 1;
    }
    if(i < l) return val;
    if(str[i] == '+') return Eval(l, i) + val;
    else return Eval(l, i) - val;
}

void tokenizer() {
    while(pos < strlen(str)) {
        if(str[pos] == ')') return;
        if(str[pos] == '(') {
            int before = pos;
            pos += 1;
            tokenizer();
            int after = pos;

            pairing[before] = after;
            pairing[after] = before;
        }
        pos += 1;
    }
}

int main() {
    memset(str, 0, sizeof(str));
    memset(pairing, -1, sizeof(pairing));
    scanf("%s", str);
    tokenizer();
    printf("%lld\n", Eval(0, strlen(str)));
}
