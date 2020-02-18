#include <iostream>
#include <cmath>
#include <memory.h>

using namespace std;
const int MAXN = 5e5 ,MAXA = 1e3;

struct Node { int parent ,kid ,left ,right ,deg ,value; } data[MAXN]; int used = 0;
class FibHeap {
    int maxi ,siz ,A[MAXA];
    void Link(int x ,int y) {
        int xl = data[x].left ,yl = data[y].left;
        data[xl].right = y; data[y].left = xl; data[x].left = yl; data[yl].right = x;
    }
    void Isolate(int x) {
        int l = data[x].left ,r = data[x].right;
        data[x].left = data[x].right = x; data[l].right = r; data[r].left = l;
    }
    void Link_Heap(int father ,int kid) {
        Isolate(kid);
        if(data[father].kid == -1) data[father].kid = kid;
        else Link(data[father].kid ,kid);
        data[kid].parent = father; data[father].deg += 1; data[father].kid = kid;
    }
    void Consolindate() {
        int arr_size = (log(siz) / log(2)) + 1; memset(A ,-1 ,sizeof(A));
        int last = data[maxi].right ,iter = maxi ,deg ,old ,head;
        bool final_round;
        do {
            final_round = (iter == last); head = iter; deg = data[iter].deg; iter = data[iter].left;
            while(A[deg] != -1) {
                old = A[deg];
                if(data[head].value < data[old].value) swap(head ,old);
                Link_Heap(head ,old); A[deg] = -1; deg += 1;
            }
            A[deg] = head;
        } while(!final_round);
        for(maxi = -1 ,iter = 0;iter < arr_size;iter++)
            if(A[iter] != -1) if(maxi == -1 || data[maxi].value < data[A[iter]].value) maxi = A[iter];
    }
public:
    int Extract() {
        int ans_value = data[maxi].value ,kid = data[maxi].kid;
        int left_shift = (data[maxi].left == maxi ? -1 : data[maxi].left);
        if(kid != -1) {
            for(int i = data[kid].left;i != kid;i = data[i].left) data[i].parent = -1;
            Link(kid ,maxi);
        }
        Isolate(maxi); maxi = (kid == -1 ? left_shift : kid);
        Consolindate(); siz -= 1;
        return ans_value;
    }
    void Meld(FibHeap* H) {
        Link(this->maxi ,H->maxi); siz += H->siz;
        if(data[H->maxi].value > data[this->maxi].value) this->maxi = H->maxi;
    }
    int Peek() { return data[maxi].value; }
    FibHeap(int value):maxi(used) ,siz(1) { data[used] = Node{-1 ,-1 ,used ,used ,0 ,value}; used += 1; }
};

int main() {
    int cmd ,value;
    FibHeap* heap = new FibHeap(0);
    while(cin >> cmd) {
        if(cmd == 1) { cin >> value; heap->Meld(new FibHeap(value)); }
        if(cmd == 2) { cout << "Extracted: " << heap->Extract() << endl; }
        if(cmd == 3) { cout << "Value: " << heap->Peek() << endl; }
    }
}
/*
1 13
1 13
1 13
1 13
2
2
2
2
2
2
2


*/
