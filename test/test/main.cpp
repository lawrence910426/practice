#include "Egg.h"

using namespace std;

long long rec(long long l ,long long r) {
    if(l + 1 == r) return l;
    if(is_broken((l + r) / 2)) {
        return rec(l ,(l + r) / 2);
    } else {
        return rec((l + r) / 2 ,r);
    }
}

long long height_limit(long long M) {
    return rec(1 ,M + 1);
}


