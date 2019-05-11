#include <iostream>
#include <tuple>

#define abs(a) (a > 0 ? a : -a)
using namespace std;
tuple<int ,int ,int> exgcd(int a ,int b) {
	if(a % b == 0) {
		//printf("%d=%d*%d+%d*%d\n" ,b ,a ,0 ,b ,1);
		return tuple<int ,int ,int>(b ,0 ,1);
	}
	if(a > b) {
		tuple<int ,int ,int> ret = exgcd(b ,a % b);
		int x = get<1>(ret) ,y = get<2>(ret) ,value = get<0>(ret) ,xx ,yy;
		xx = y ,yy = x - (a / b) * y;
		//printf("%d=%d*%d+%d*%d\n" ,value ,a ,xx ,b ,yy);
		return tuple<int ,int ,int>(value ,xx ,yy);	
	} else {
		tuple<int ,int ,int> ret = exgcd(b ,a);
		return tuple<int ,int ,int>(get<0>(ret) ,get<2>(ret) ,get<1>(ret));
	}
}

int main() {
	int a ,b ,x ,y ,gcd ,x1 ,y1 ,x2 ,y2;
	while(cin >> a >> b) {
		tuple<int ,int ,int> ret = exgcd(a ,b);
		gcd = get<0>(ret) ,x = get<1>(ret) ,y = get<2>(ret);
		
		while(true) {
			x1 = x + b / gcd ,y1 = y - a / gcd;
			x2 = x - b / gcd ,y2 = y + a / gcd;
			
			/*printf("%d=%d*%d+%d*%d\n" ,gcd ,a ,x1 ,b ,y1);
			printf("%d=%d*%d+%d*%d\n" ,gcd ,a ,x ,b ,y);
			printf("%d=%d*%d+%d*%d\n" ,gcd ,a ,x2 ,b ,y2);
			system("pause");*/
			
			if(abs(x2) + abs(y2) <= abs(x) + abs(y) && abs(x2) + abs(y2) <= abs(x1) + abs(y1)) x = x2 ,y = y2;
			else if(abs(x1) + abs(y1) < abs(x) + abs(y) && abs(x1) + abs(y1) < abs(x2) + abs(y2)) x = x1 ,y = y1;
			else break;
		}
		
		printf("%d %d %d\n" ,x ,y ,gcd);
		//printf("%d=%d*%d+%d*%d\n" ,gcd ,a ,x ,b ,y);
	}
}

/*
6 4
17 13
21 7
*/
