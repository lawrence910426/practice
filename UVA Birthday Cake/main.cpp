#include <iostream>
#include <algorithm>
#include <cmath>
#define pi (atan2(0 ,-1))
#define abs(x) ((x) > 0 ? (x) : -(x))
using namespace std;
struct point {
	int rawx ,rawy ,code;
	float degree;
}data[100000];

bool cmp(point a, point b) {
	return a.degree < b.degree;
} 

int main() {
	int N;
	int i ,j;
	point *l ,*r ,tmp;
	float length ,deg ,dega ,degb;
	while(cin >> N ,N) {
		for(i = 0;i != N * 2;i++) {
			cin >> data[i].rawx >> data[i].rawy;
			deg = atan2(data[i].rawy ,data[i].rawx);
			if(deg < 0) deg += 2 * pi;
			data[i].degree = deg / pi * 180;
		}
		sort(data ,data + N * 2 ,cmp);
		for(i = 0;i != N * 2;i++) data[i].code = i;
		
		for(i = -500;i <= 500;i++) for(j = -500;j <= 500;j++) {
			if(i == 0 && j == 0) continue;
			
			dega = atan2(-i ,j) / pi * 180;
			if(dega < 0) dega += 360; 
			if(dega > 180) degb = dega - 180;
			else degb = dega + 180;
			
			tmp.degree = dega;
			l = lower_bound(data ,data + 2 * N ,tmp ,cmp);
			if(l == data + 2 * N) l = data;
			if(l->rawx * i + l->rawy * j == 0) continue;
			
			tmp.degree = degb;
			r = lower_bound(data ,data + 2 * N ,tmp ,cmp);
			if(r == data + 2 * N) r = data;
			if(r->rawx * i + r->rawy * j == 0) continue;
			
			if(abs(l->code - r->code) == N) {
				/*printf("(%d,%d) (%d,%d) %f %f\n" ,i ,j ,-i ,j  ,dega ,degb);
				printf("%d %d %d %f\n" ,l->code ,l->rawx ,l->rawy ,l->degree);
				printf("%d %d %d %f\n" ,r->code ,r->rawx ,r->rawy ,r->degree);
				system("pause");*/
				
				cout << i << " " << j << endl;
				i = j = 1000;
				
			}
		}
	}
}

