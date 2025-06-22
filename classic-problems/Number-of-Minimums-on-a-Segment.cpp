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
};

auto operation = [](pair<int,int> a, pair<int,int> b) {
  if(a.first == b.first){
    return make_pair(a.first, a.second + b.second);
  }

  if(a.first < b.first){
    return a;
  } else {
    return b;
  }
};

signed main()
{ 
  _
  int n, q; cin >> n >> q;
  vector<pair<int,int>> a(n);
  for(int i = 0; i < n;i++) {
    int aux; cin >> aux;
    a[i] = {aux,1};
  }



  SegTree<pair<int,int>,decltype(operation)> 
  seg(n,operation, make_pair(LINF,0));

  seg.init(a);
  dbg(seg.tree);

  while(q--){
    int op; cin >> op;
    if(op == 1){
      int idx, val; cin >> idx >> val;
      seg.update(idx, make_pair(val,1));
    } else {
      int l,r; cin >> l >> r;
      auto ans = seg.query(l,r-1);
      cout << ans.first << " " << ans.second << endl;
    }
  }

  return 0;
}
