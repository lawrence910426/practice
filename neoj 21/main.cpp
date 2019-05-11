#include <iostream>

using namespace std;
struct p{
	int prev ,next ,val;
}data[1000000];
int front ,last;

int main() {
	int n ,m ,cmd ,ptr;			int i ,a ,b ,c ,d;
	while(cin >> n >> m)
	{
		front = 1 ,last = n;
		for(i = 1;i <= n;i++) 
			data[i].val = i,
			data[i].prev = (i == 1 ? -1 : i - 1),
			data[i].next = (i == n ? -1 : i + 1);
		while(m--)
		{
			if(cin >> cmd ,cmd == 0)
			{
				cin >> cmd;
				a = data[cmd].prev ,b = data[cmd].next;
				if(a == -1) front = b; 
				else data[a].next = b;
				
				if(b == -1) last = a;
				else data[b].prev = a;
			}
			else
			{
				cin >> cmd;
				if(cmd == front) continue;
				c = cmd ,d = data[cmd].next ,b = data[cmd].prev ,a = data[b].prev;
				if(a == -1) front = c;
				else data[a].next = c;
				if(d == -1) last = b;
				else data[d].prev = b;
				data[b].next = d ,data[b].prev = c;
				data[c].next = b ,data[c].prev = a;
			}
		}
		
		ptr = front;
		while(ptr != last) cout << data[ptr].val << " " ,ptr = data[ptr].next;
		cout << data[ptr].val << endl;
	}
}
