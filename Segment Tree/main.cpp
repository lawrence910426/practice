#include <iostream>
#define max(a ,b) (a > b ? a : b)
#define min(a ,b) (a < b ? a : b)
#pragma GCC optimize ("O3")
using namespace std;
int data[500005];

class node {
	node *l ,*r;
	int value ,left ,right;
	
public:
	node(int left ,int right) {
		this->left = left ,this->right = right;
		if(left == right) {
			value = data[left];	
		}
		else {
			l = new node(left ,(left + right) / 2);
			r = new node((left + right + 1) / 2 ,right);
			merge();
		}
	}
	
	void merge() {
		value = max(l->value ,r->value);
	}
	
	void modify(int x ,int v) {
		if(left <= x && x <= right) {
			if(left == right && left == x) {
				this->value = v;
			} else {
				l->modify(x ,v);
				r->modify(x ,v);
				merge();	
			}
		} else return;
	}
	
	int query(int left ,int right) {
		int lvalue = -1 ,rvalue = -1;
		if(left == this->left && right == this->right) return this->value;
		if(l->left <= left && left <= l->right) lvalue = l->query(left ,min(right ,l->right));
		if(r->left <= right && right <= r->right) rvalue = r->query(max(left ,(r->left)) ,right);
		//printf("L[%d,%d],Q[%d,%d]:%d\n" ,this->left + 1,this->right + 1,left + 1 ,right + 1 ,max(lvalue ,rvalue));
		return max(lvalue ,rvalue);
	}
};

int main(int argc, char** argv) {
	int N ,q ,l ,r ,x ,v;
	char cmd;
	int i;
	ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
	while(cin >> N) {
		for(i = 0;i < N;i++) cin >> data[i];
		node* st = new node(0 ,N);
		for(cin >> q;q--;) {
			/*cin >> cmd;*/
			/*if(cmd == 'q') cin >> l >> r ,cout << st->query(l ,r) << endl;*/
			/*if(cmd == 'm') cin >> x >> v ,st->modify(x ,v);*/
			cin >> l >> r;
			if(l > r) l ^= r ,r ^= l ,l ^= r;
			cout << st->query(l - 1 ,r - 1) << endl;
		}
	}
}
