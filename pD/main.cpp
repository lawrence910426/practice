#include <iostream>
#include <cstring>
#include <vector>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define singular(a) (a == 'o' || a == 'v' || a == 'w' || a == 'x' || a == '8')
#define doublar(a) (a == 'b' || a == 'q' || a == 'd' || a == 'p')
#define mirror(a ,b) ((a == 'b' && b == 'd') || (a == 'd' && b == 'b') || (a == 'q' && b == 'p') || (a == 'p' && b == 'q'))

using namespace std;
int main(int argc, char** argv) {
	string data;
	int i ,j;
	int maxi;
	bool fail;
	
	ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
	while(cin >> data) {
		vector<pair<int ,int> > points;
		for(i = 0;i < data.size();i++) {
			if(singular(data[i])) {
				for(j = 0;;j++) {
					if(i - j < 0 || data.size() <= i + j) break;
					if(mirror(data[i - j] ,data[i + j]) || data[i - j] == data[i + j]) ;
					else break;
				}
				
				if(j == 0) points.push_back(pair<int ,int>(i ,i));
				else {
					j -= 1;
					points.push_back(pair<int ,int>(i - j ,i + j));
				}
				
			}
			if(doublar(data[i])) {
				for(j = 0;;j++) {
					if(i - j < 0 || data.size() <= i + j + 1) break;
					if(mirror(data[i - j] ,data[i + j + 1]) || data[i - j] == data[i + j + 1]) ;
					else break;
				}
				
				if(i < 0 || data.size() <= i + 1 || !(mirror(data[i] ,data[i + 1]) || data[i] == data[i + 1])) ;
				else {
					if(j == 0) points.push_back(pair<int ,int>(i ,i + 1));
					else {
						j -= 1;
						points.push_back(pair<int ,int>(i - j ,i + j + 1));
					}
				}
			}
		}
		
		if(points.size() == 0) {
			cout << "...\n";
		} else {
			for(maxi = i = 0;i < points.size();i++) {
				if(points[i].second - points[i].first > points[maxi].second - points[maxi].first) maxi = i;
				/*cout << points[i].first << " " << points[i].second << " ";
				for(j = points[i].first;j <= points[i].second;j++) cout << data[j];
				cout << endl;*/
			}
				
			for(i = points[maxi].first;i <= points[maxi].second;i++) cout << data[i];
			cout << endl;
		}

	}
}

/*
vxvbpqd
*/
