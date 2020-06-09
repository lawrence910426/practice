#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#define int_max (1LL << 31 - 1)
using namespace std;
int ways[6][3] = {{0 ,1 ,2} ,{1 ,0 ,2} ,{0 ,2 ,1} ,{2 ,0 ,1} ,{1 ,2 ,0} ,{2 ,1 ,0}};
int data[3] ,d;
int dp[201][201][201] ,result[1000];
queue<int> jug_status[3] ,moved;

int main(int argc, char** argv) {
	int T;
	int i ,j ,k;
	for(cin >> T;T--;) {
		cin >> data[0] >> data[1] >> data[2] >> d;
		for(i = 0;i < 3;i++) jug_status[i] = queue<int>();
		moved = queue<int>();
		for(i = 0;i < 201;i++) {
			result[i] = int_max;
			for(j = 0;j < 201;j++) for(k = 0;k < 201;k++) dp[i][j][k] = int_max;
		}
		jug_status[0].push(0) ,jug_status[1].push(0) ,jug_status[2].push(data[2]) ,moved.push(0);
		
		while(!moved.empty()) {
			if(dp[jug_status[0].front()][jug_status[1].front()][jug_status[2].front()] <= moved.front()) {
				for(i = 0;i < 3;i++) jug_status[i].pop();
				moved.pop();
				continue;
			}
			//printf("%d %d %d %d\n" ,jug_status[0].front() ,jug_status[1].front() ,jug_status[2].front() ,moved.front());
			dp[jug_status[0].front()][jug_status[1].front()][jug_status[2].front()] = moved.front();
			for(i = 0;i < 3;i++) result[jug_status[i].front()] = min(result[jug_status[i].front()] ,moved.front());
			
			for(i = 0;i < 6;i++) {
				if(data[ways[i][0]] - jug_status[ways[i][0]].front() > jug_status[ways[i][1]].front()) { //unable to fill
					jug_status[ways[i][0]].push(
						jug_status[ways[i][0]].front() + jug_status[ways[i][1]].front()
					);
					jug_status[ways[i][1]].push(
						0
					);
					jug_status[ways[i][2]].push(
						jug_status[ways[i][2]].front()
					);
					moved.push(
						moved.front() + jug_status[ways[i][1]].front()
					);
				} else { //could be filled
					jug_status[ways[i][0]].push(
						data[ways[i][0]]
					);
					jug_status[ways[i][1]].push(
						jug_status[ways[i][1]].front() - data[ways[i][0]] + jug_status[ways[i][0]].front()
					);
					jug_status[ways[i][2]].push(
						jug_status[ways[i][2]].front()
					);
					moved.push(
						moved.front() + data[ways[i][0]] - jug_status[ways[i][0]].front()
					);
				}
			}
			for(j = 0;j < 3;j++) jug_status[j].pop();
			moved.pop();
		}
		
		for(i = d;i >= 0;i--) 
			if(result[i] != int_max)
				break;
		cout << result[i] << " " << i << endl;
		
	}
}


// The code is not tested.
