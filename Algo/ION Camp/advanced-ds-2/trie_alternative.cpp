#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <memory.h>
#include <algorithm>
#include <assert.h>

using namespace std;

const int MAXN = 1e5 + 50, MAXC = 1e4;

class Trie {
    unordered_map<bitset<MAXC>, int> storage;
public:
    bitset<MAXC> lazy_tag;
    Trie() { lazy_tag.reset(); }
    void Modify(bitset<MAXC>& key, int diff) { storage[key] += diff; }
    int Query(bitset<MAXC>& key) { return storage[key]; }
} Suffixes;

class Sieve {
    long long prime[MAXN];
    vector<long long> ps;
public:
    Sieve() {
        for(int i = 0;i < MAXN;i++) prime[i] = i;
        for(long long i = 2;i < MAXN;i++) {
            if(prime[i] == i) ps.push_back(i);
            for(long long j : ps) {
                if(i * j >= MAXN) break;
                prime[i * j] = j;
                if(i % j == 0) break;
            }
        }
    }

    void Factorization(int value, unordered_map<int, int>& result) {
        for(result.clear();value != 1;value /= prime[value]) result[prime[value]] = result[prime[value]] + 1;
    }
} LinearSieve;

class Discretion {
    vector<int> domain;
public:
    Discretion() { }
    void Insert(int item) { domain.push_back(item); }
    void Init() {
        sort(domain.begin(), domain.end());
        domain.erase(unique(domain.begin(), domain.end()), domain.end()); 
    }
    int get_code(int original) { return lower_bound(domain.begin(), domain.end(), original) - domain.begin(); }
    int get_original(int code) { return domain[code]; }
    int get_size() { return domain.size(); }
} Discrete;

unordered_set<int> factors[MAXN];
unordered_map<int, int> factored;
bitset<MAXC> factor_temp;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N;
    int i, temp;
    long long ans = 0;
    
    cin >> N;
    for(i = 0;i < N;i++) { 
        cin >> temp; 
        LinearSieve.Factorization(temp, factored); 
        for(auto p : factored) if(p.second % 2 == 1) factors[i].insert(p.first);
    }
    for(i = 0;i < N;i++) for(int p : factors[i]) Discrete.Insert(p);
    Discrete.Init();
    for(i = 0;i < N;i++) {
        factor_temp.reset();
        for(int p : factors[i]) factor_temp[Discrete.get_code(p)] = true;
        Suffixes.Modify(Suffixes.lazy_tag, 1);
        Suffixes.lazy_tag ^= factor_temp;
        ans += Suffixes.Query(Suffixes.lazy_tag);
    }
    cout << ans << '\n';
}