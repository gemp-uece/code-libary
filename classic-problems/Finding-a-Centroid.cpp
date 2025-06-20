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

int n, subsize[MAX];
vector<int> g[MAX];

void dfs(int k, int p=-1) {
  subsize[k] = 1;
  for (int i : g[k]) if (i != p) {
    dfs(i, k);
    subsize[k] += subsize[i];
  }
}

int centroid(int k, int p=-1, int size=-1) {
  if (size == -1) size = subsize[k];
  for (int i : g[k]) if (i != p) if (subsize[i] > size/2)
    return centroid(i, k, size);
  return k;
}

pair<int, int> centroids(int k=0) {
  dfs(k);
  int i = centroid(k), i2 = i;
  for (int j : g[i]) if (2*subsize[j] == subsize[k]) i2 = j;
  return {i, i2};
}

signed main()
{ 
  _
  cin >> n;
  for(int i = 1; i < n; i++){
    int u, v; cin >> u >> v; u--;v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto ans = centroids();

  cout << ans.first + 1 << endl;


  return 0;
}
