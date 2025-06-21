// https://www.spoj.com/problems/INVCNT/en/

#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int long long
typedef long long ll;
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

const int MAX = 200005;
const ll LINF = 0x3f3f3f3f3f3f3f3fll; 

vector<int> a(MAX), tree[4*MAX];

void build(int node, int start, int end){

  if(start == end) tree[node] = {a[start]};
  else{
    int mid = (start+end)/2;
    build(2*node,start,mid);
    build(2*node+1,mid+1,end);
    tree[node].resize(tree[2*node].size() + tree[2*node+1].size());
    merge(
      tree[2*node].begin(), tree[2*node].end(),
      tree[2*node+1].begin(),tree[2*node+1].end(),
      tree[node].begin()
    );
  }
}

int query(int node, int start, int end, int l, int r, int k){
  if(start > r or end < l){
    return 0;
  }
  if(l <= start and end <= r){
    return lower_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
  }

  int mid = (start + end)/2;
  int p1 = query(2*node, start,mid,l,r,k);
  int p2 = query(2*node+1,mid+1,end,l,r,k);
  return p1 + p2;
}

signed main()
{ 
  _
  int t; cin >> t;
  while(t--){
    int n; cin >> n;
    for(int i = 0; i < n; i++){
      cin >> a[i];
    }

    build(1,0,n-1);
    int ans = 0;
    for(int i = 0; i < n-1; i++){
      ans += query(1,0,n-1,i+1,n-1,a[i]);
    }
    cout << ans << endl;
  }


  return 0;
}
