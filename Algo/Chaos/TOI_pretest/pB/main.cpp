#include <iostream>
#include <stack>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct b{
	int height ,width;
}data[3000];


using namespace std;
int main() {
	int t ,n ,ans ,ans_tmp ,eax_ans ,ebx_ans; 
	int i ,counter;
	stack<b> q ,tmp ,eax ,ebx;
	for(cin >> t,counter = 0;counter != t;counter++)
	{
		for(cin >> n ,i = 0;i != n;i++) cin >> data[i].height;
		for(i = 0;i != n;i++) cin >> data[i].width;
		q = stack<b>();
		for(ans = 0 ,i = 0;i != n;i++)
			if(q.empty()) q.push(data[i]) ,ans += data[i].width;
			else
				if(q.top().height < data[i].height) q.push(data[i]) ,ans += data[i].width;
				else
					if(q.top().width > data[i].width) continue;
					else
					{
						tmp = stack<b>(q) ,ans_tmp = ans;
						while(!tmp.empty() && tmp.top().height >= data[i].height) ans_tmp -= tmp.top().width, tmp.pop();
						ans_tmp += data[i].width ,tmp.push(data[i]);
						
						if(ans_tmp == ans)
						{
							if(tmp.top().height < q.top().height) q = stack<b>(tmp);
							else if(tmp.top().height > q.top().height) ;	//do nothing.
							else if(tmp.top().height == q.top().height)
							{
								eax = stack<b>(q) ,ebx = stack<b>(tmp);
								eax_ans = ans ,ebx_ans = ans_tmp;
								while(!(eax.empty() || ebx.empty()) &&
									eax.top().height == ebx.top().height && eax.top().width == ebx.top().width)
									eax_ans -= eax.top().width ,ebx_ans -= ebx.top().width
									,eax.pop() ,ebx.pop();
								if(eax.empty()) { q = stack<b>(tmp); continue; }
								if(ebx.empty()) continue;
								if(eax_ans == ebx_ans)
									if(eax.top().height > ebx.top().height) q = stack<b>(tmp);	//if equals ,doesn't matter.
								if(eax_ans < ebx_ans) q = stack<b>(tmp);
								if(eax_ans > ebx_ans) continue;
							}
						}
						if(ans_tmp < ans) ;	//do nothing.
						if(ans_tmp > ans) ans = ans_tmp ,q = stack<b>(tmp);
					}
		printf("Case %d. Increasing (%d).\n" ,counter + 1 ,ans);
	}
	return 0;
}
