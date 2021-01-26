#include <set>
#include <random>

using namespace std;

#define magic 8071097
#define bf(x) ((x * 3) % magic)

class RBTree {
	multiset<int> S;
	multiset<int>::iterator it = S.end();
public:
	void insert(int i) {
		if(it == S.end()) it = S.insert(i);
		else it = S.emplace_hint(it, i);
	}
	void erase(int i) {
		auto it = S.find(i);
		if(it != S.end()) S.erase(it);
	}
};

int main() {
  srand(magic);
  RBTree tree;

  for (int i = 0; i < magic; i++)
    tree.insert(i);

  for (int i = 0; i < magic; i++) {
    if (rand() % 2) {
      tree.insert(bf(i));
    } else {
      tree.erase(bf(i));
    }
  }
  return 0;
}
