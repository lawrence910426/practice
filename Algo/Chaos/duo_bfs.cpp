#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;
struct state { 
	int Step, X, Y;
	struct { unsigned long long value : 4; } item[4][4]; 
};

bool insert(queue<state>& Q, unordered_set<unsigned long long>& S, state X) {
	Q.push(X);
	unsigned long long H = 0;	
	for(int i = 0;i < 16;i++) H |= (unsigned long long)(X.item[i / 4][i % 4].value) << (4 * i);
	if(S.find(H) != S.end()) return true;
	S.insert(H);
	return false;
}

bool solve(state A, state B) {
	state Temp;
	queue<state> Q;
	unordered_set<unsigned long long> S;
	int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0}, x, y;
	for(insert(Q, S, A), insert(Q, S, B);!Q.empty();Q.pop()) {
		for(int i = 0;i < 4;i++) {
			Temp = Q.front();
			x = Temp.X + dx[i];
			y = Temp.Y + dy[i];
			if(x < 0 || 4 <= x || y < 0 || 4 <= y) continue;
			swap(Temp.item[x][y], Temp.item[Temp.X][Temp.Y]);
			Temp.X = x;
			Temp.Y = y;
			Temp.Step = Q.front().Step + 1;
			if(Temp.Step >= 20) continue;
			if(insert(Q, S, Temp)) return true;
		}
	}
	return false;
}

int main() {
	int value;
	state A, B;
	for(int i = 0;i < 4;i++) for(int j = 0;j < 4;j++) A.item[i][j].value = i * 4 + j;	
	for(int i = 0;i < 4;i++) for(int j = 0;j < 4;j++) {
		cin >> value;
		B.item[i][j].value = value;
	}
	A.Step = B.Step = 0;
	for(int i = 0;i < 4;i++) for(int j = 0;j < 4;j++) {
		if(A.item[i][j].value == 0) {
			A.X = i;
			A.Y = j;
		}
		if(B.item[i][j].value == 0) {
			B.X = i;
			B.Y = j;
		}
	}
	cout << (solve(A, B) ? "Yes" : "No") << endl;
}
