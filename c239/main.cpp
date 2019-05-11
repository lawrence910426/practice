#include <iostream>
#include <memory.h> 
#include <vector>
#include <bitset>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define MAX_N 16
#define adapt(number)((number == -1 ? (1LL << 31) - 1 : number))

using namespace std;
struct t{
	int maxi ,mini;
	vector<int> max_src ,min_src;
}tsm[MAX_N][1 << MAX_N]; 
int data[MAX_N][MAX_N];

bool is_single(int i)
{
	while(!(i & 1)) i = (i >> 1);
	return i == 1;
}

int main() {
	int n;					int i ,j ,k;		t tmp;
	while(cin >> n)
	{
		for(i = 0;i < n;i++) for(j = i + 1;j < n;j++)
			cin >> data[i][j] ,data[j][i] = data[i][j];
		
		for(i = 0;i != n;i++) for(j = 0;j != (1 << n);j++)
		{
			tsm[i][j].maxi = -1;
			tsm[i][j].mini = (1LL << 31) - 1;
		} 
		for(i = 0;i != n;i++) for(j = 0;j != n;j++)
		{
			tsm[i][1 << j].mini = tsm[i][1 << j].maxi = data[i][j];
			tsm[i][1 << j].max_src = vector<int>(j);
			tsm[i][1 << j].min_src = vector<int>(j);
		} 
		
		for(i = 1;i <= (1 << n);i++)
		{
			if(is_single(i)) continue;
			for(j = 0;j != n;j++)
			{
				if((i >> j) & 1) continue;
				for(k = 0;(1 << k) <= i;k++)
				{
					if(j == k) continue;
					if((i >> k) & 1)
					{
						tsm[j][i].mini = min(tsm[j][i].mini ,tsm[k][i - (1 << k)].mini + data[k][j]);
						tsm[j][i].maxi = max(tsm[j][i].maxi ,tsm[k][i - (1 << k)].maxi + data[k][j]); 
						
						cout << "new_location: " << j << "\tnew_path: " << std::bitset<8>(i) << "\tnew_value: " << tsm[j][i].mini << endl
							<< "old_location: " << k << "\told_path: " << std::bitset<8>(i - (1 << k)) << "\told_value: " << tsm[k][i - (1 << k)].mini << endl << endl;
					}
				}
			}
		}
		
		for(i = 0;i != n;i++)
		{
			tmp = tsm[i][(1 << n) - 1 - (1 << i)];
			cout << i << " " << tmp.maxi << " " << tmp.mini << endl;
		}
	}
	return 0;
}
