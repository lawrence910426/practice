#include <iostream>
#include <algorithm>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct item {
	int weight ,use;
}data[100000];
using namespace std;

bool cmp(item a ,item b)
{
	return a.weight * b.use < a.use * b.weight;
}

int main(int argc, char** argv) {
	int n ,i;
	long long int ans ,sum;
	
	while(cin >> n)
	{
		for(i = 0;i != n;i++) cin >> data[i].weight;
		for(i = 0;i != n;i++) cin >> data[i].use;
	
		sort(data ,data + n ,cmp);
		/*for(i = 0;i != n;i++)
			printf("%d %d\n" ,data[i].weight ,data[i].use);*/
		
		for(i = ans = sum = 0;i != n;i++) 
			ans += sum * data[i].use,
			sum += data[i].weight;
		cout << ans << endl;
	}
}
