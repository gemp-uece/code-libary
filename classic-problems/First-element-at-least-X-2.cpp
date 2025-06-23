// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/D

#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int long long
typedef long long ll;
#define sz(x) (int)x.size() 
#ifdef DEBUG
    #define dbg(x) cerr << #x << " = "; _print(x); cerr << endl;
#else
    #define dbg(x)
#endif
#define TxtIO   freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);

void _print(long long x) { cerr << x; }
void _print(string x) { cerr << '"' << x << '"'; }
void _print(char x) { cerr << '\'' << x << '\''; }
void _print(bool x) { cerr << (x ? "true" : "false"); }
void _print(float x) { cerr << x; }

template<typename T, typename V> void _print(pair<T, V> p) { cerr << "{"; _print(p.first); cerr << ", "; _print(p.second); cerr << "}"; }
template<typename T> void _print(vector<T> v) { cerr << "["; for (auto &i : v) { _print(i); cerr << ", "; } cerr << "]"; }
template<typename T> void _print(set<T> s) { cerr << "{"; for (auto &i : s) { _print(i); cerr << ", "; } cerr << "}"; }
template<typename T, typename V> void _print(map<T, V> m) { cerr << "{"; for (auto &i : m) { _print(i); cerr << ", "; } cerr << "}"; }

const int MAX = 2e5+5;
const ll LINF = 0x3f3f3f3f3f3f3f3fll; 
const int MINF = -1e18;
const int MOD = 1e8;

#define esq node << 1ll
#define dir (node << 1) | 1ll

// T -> Node e F -> operação


template<typename T, typename F>
struct SegTree {
  vector<T> tree;
  int size;
  F operation;
  T neutral;

  SegTree(){}

  SegTree(int n, F op, T neutral_elem) : size(n), operation(op), neutral(neutral_elem){
    size = n;
    tree.resize(size << 2, neutral);
  }

  void build(int node, int start, int end, vector<T> &a){
    if(start == end){
      tree[node] = a[start];
      return;
    }

    int mid = (start + end) >> 1;
    build(esq,start,mid,a);
    build(dir,mid+1,end,a);
    tree[node] = operation(tree[esq],tree[dir]);
  }

  void init(vector<T> &a){
    build(1,0,size - 1, a);
  }

  void update(int node, int start, int end, int idx,const T &v){
    if(start == end){
      tree[node] = v;
      return;
    }

    int mid = (start + end)/2;
    if(idx <= mid)
      update(esq,start,mid, idx,v);
    else
      update(dir,mid+1,end,idx,v);
    tree[node] = operation(tree[esq],tree[dir]);
  }

  void update(int idx, const T &v){
    update(1,0,size - 1, idx, v);
  }

  T query(int node, int start, int end, int l, int r){
    if(r < start or l > end) return neutral; // changed to return the minimum
    if(l <= start and end <= r) return tree[node];
    int mid = (start + end) >> 1;
    return operation(query(esq, start, mid, l, r),query(dir, mid+1, end, l, r));
  }

  T query(int l, int r){
    return query(1,0,size - 1, l, r);
  }

  // para achar o k esimo 1 em uma sequencia de 0 ou 1's. 
  // deve atualizar o update tambem.
  int find_kth_one(int node, int l, int r, int k){
    if(l == r) return l;
    int s = tree[2*node];
    int mid = (l+r)/2;
    if(k < s) return find_kth_one(2*node,l,mid,k);
    return find_kth_one(2*node+1,mid+1,r,k - s);
  }

  // Para achar o primeiro elemento maior que ou igual a x.
  // manter a operação como o maximo.
  int find_greater_than(int node, int l, int r, int x){
    if(tree[node] < x){
      return -1;
    }

    if(l == r) {
      return l;
    }
    int s = tree[2*node];
    int mid = (l+r)/2;
    if(s >= x){
      return find_greater_than(2*node,l,mid,x);
    } else{
      return find_greater_than(2*node+1,mid+1,r,x);
    }
  }

  int find_first_above(int node, int l, int r, int x, int ql){
    if(tree[node] < x || r < ql){
      return -1;
    }

    if(l == r) return l;

    int mid = (l+r)/2;
    int left = find_first_above(2*node, l, mid,x,ql);
    if(left != -1) return left;
    return find_first_above(2*node+1, mid+1,r,x,ql);
  }



};

/**
1.Para mínimo de inteiros:
auto min_op = [](int a, int b) { return min(a, b); };
SegTree<int, decltype(min_op)> st(n, min_op, LLONG_MAX);
 
2.Para máximo de pares:
auto max_pair = [](pair<int,int> a, pair<int,int> b) { return max(a, b); };
SegTree<pair<int,int>, decltype(max_pair)> st(n, max_pair, make_pair(INT_MIN, INT_MIN));


3. Para união de sets:
auto set_union = [](const set<int>& a, const set<int>& b) {
    set<int> res = a;
    res.insert(b.begin(), b.end());
    return res;
};
SegTree<set<int>, decltype(set_union)> st(n, set_union, set<int>());


4. Para soma de mapas:
auto map_sum = [](const map<int,int>& a, const map<int,int>& b) {
    map<int,int> res = a;
    for (auto& [k, v] : b) res[k] += v;
    return res;
};
SegTree<map<int,int>, decltype(map_sum)> st(n, map_sum, map<int,int>());
 * */

struct Node {
  int sum; // sum;

  Node(int v = 0): sum(v) {}
};

auto operation = [](const int& a,const int& b) {
  return max(a,b);
};

signed main()
{ 
  _
  int n,q; cin >> n >> q;
  vector<int> a(n);
  for(int i = 0; i < n; i++){
    cin >> a[i];
  }
  SegTree<int, decltype(operation)> segT(n, operation, 0);
  segT.init(a);
  while(q--){
    int op; cin >> op;
    if(op == 1){
      int idx,val; cin >> idx >> val;
      segT.update(idx,val);
    } else{
      int x, l; cin >> x >> l;
      cout << segT.find_first_above(1,0,n-1,x,l) << endl;
    }
  }

  return 0;
}
