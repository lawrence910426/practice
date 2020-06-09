#include <iostream>
#include <vector>
#include <algorithm>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
struct rock {
	int pos;
	bool drown ,used;
};
int T ,n ,D;
vector<rock> data;

bool cmp(rock a ,rock b) {
	return a.pos < b.pos;
}

bool able(int dist) {
	int pos = 0;
	rock tmp;
	vector<rock>::iterator it;
	while(pos < D) {
		tmp.pos = pos + dist;
		it = lower_bound(data.begin() ,data.end() ,tmp ,cmp);
		while(it == data.end() || it->pos > pos + dist || it->used) it--;
		if(it->drown) it->used = true;	
		if(it->pos == 0 || it->pos == pos) return false;
		pos = it->pos;
	}
	while(0 < pos) {
		tmp.pos = pos - dist;
		it = lower_bound(data.begin() ,data.end() ,tmp ,cmp);
		while(it->used) it++;
		if(it->drown) it->used = true;	
		if(it->pos == D || it->pos == pos) return false;
		pos = it->pos;
	}
	return true;
}

int search(int l ,int r) {
	int i ,center = (l + r) / 2;
	if(l == r) return l;
	//printf("%d %d\n", l,r);
	
	for(i = 0;i < data.size();i++) data[i].used = false;
	if(l == r - 1) {
		if(able(r)) return r;
		else return l;
	}
	if(able(center)) {
		return search(l ,center);
	} else {
		return search(center ,r);
	}
}

int main(int argc, char** argv) {
	int i ,d ,counter = 0;
	char c;
	rock tmp;
	for(cin >> T;T--;) {
		data = vector<rock>();
		cin >> n >> D;
		
		tmp.used = false;
		for(i = 0;i < n;i++) {
			cin >> c >> d;
			d = -d;
			tmp.pos = d ,tmp.drown = c == 'S';
			//cout << c << endl;
			data.push_back(tmp);
		}
		tmp.pos = 0 ,tmp.drown = false ,data.push_back(tmp);
		tmp.pos = D ,tmp.drown = false ,data.push_back(tmp);
		sort(data.begin() ,data.end() ,cmp);
		
		cout << "Case " << ++counter << ": " << search(0 ,D) << endl;
	}
}
