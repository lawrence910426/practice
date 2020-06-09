#include "Egg.h"

//----do not modify above----

long long height_limit(long long M) {
    long long L = 1 ,R = M + 1 ,mid;
    while(L != R - 1) {
        mid = (L + R) / 2;
        if(is_broken(mid)) R = mid;
        else L = mid;
    }
    return L;
}


//----do not modify below----

#ifndef EVAL
long long _M, _h;

int _count = 0;

bool is_broken(long long k){
	_count++;
	if(_count > 60){
		printf("Wrong Answer: too many queries\n");
		exit(0);
	}
	if(k > _M){
		printf("Wrong Answer: invalid broken query\n");
		exit(0);
	}
	return k > _h;
}

int main() {
	long long hl, ret;
	ret = scanf("%lld %lld", &_M, &_h);
	hl = height_limit(_M);
	if(hl == _h)
		printf("Accept: %d\n", _count);
	else
		printf("Wrong Answer: incorrect height\n");
}
#endif
