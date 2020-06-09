#pragma GCC optimize("Ofast,unroll-loops")

#include <iostream>
#include <memory.h>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 5e5 ,MAXA = 50;
struct Node { int parent ,kid ,left ,right ,deg ,value; } data[MAXN]; int used = 0 ,A[MAXA];
class FibHeap {
    int maxi ,siz;
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

long long Budget ,Ans;
struct { int boss; long long cost ,lead; vector<int> kids; } Ninja[MAXN];
struct catalogue { long long cost ,amount; FibHeap* heap; } Ret[MAXN];

void Dfs(int on) {
    Ret[on].heap->Meld(new FibHeap(0));
    for(int K : Ninja[on].kids) {
        Dfs(K); Ret[on].heap->Meld(Ret[K].heap);
        Ret[on].cost += Ret[K].cost; Ret[on].amount += Ret[K].amount;
    }
    while(Ret[on].cost > Budget) { Ret[on].cost -= Ret[on].heap->Extract(); Ret[on].amount -= 1; }
    Ans = max(Ans ,Ret[on].amount * Ninja[on].lead);
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,i;
    cin >> N >> Budget;
    Ninja[0].boss = Ninja[0].cost = Ninja[0].lead = 0;
    for(i = 1;i <= N;i++) {
        cin >> Ninja[i].boss >> Ninja[i].cost >> Ninja[i].lead;
        Ninja[Ninja[i].boss].kids.push_back(i);
    }
    for(i = 0;i <= N;i++) Ret[i] = catalogue{Ninja[i].cost ,1 ,new FibHeap(Ninja[i].cost)};
    Ans = -1; Dfs(0); cout << Ans << '\n';
}
