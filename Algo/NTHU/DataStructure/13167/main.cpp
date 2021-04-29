#include <iostream>
using namespace std;

class Node {
	Node *l, *r, *d, *u;
	long long X, Y;
public:
	Node(long long X, long long Y) {
		l = r = d = u = this;
		this->X = X;
		this->Y = Y;
	}
};

class Index {
	Node* storage = nullptr;
	long long id;
	Index *l, *r;
public:
	Index(long long id) {
		l = r = this;
		this->id = id;
	}

	Index* InsertBehind(Index* item) {
		
	}

	void InsertNode(long long X, long long Y) {

	}
};

class Root {
	Index *X, *Y;
public:
	Root() {
		X = new Index(0);
		Y = new Index(0);
	}

	void Insert(long long x, long long y) {
		Index *ptr = X;
		do {
			if(ptr->id < x && x < ptr->r->id && ptr->id < ptr->r->id) ptr->InsertBehind(new Index(x));
			if(ptr->id == x) 
			ptr = ptr->r;
		} while(ptr != X);
	}

	void Erase(long long x, long long y) {

	}

	void Traverse(int tag) {

	}
} *Matrix = new Root();

int main() {
	
}
