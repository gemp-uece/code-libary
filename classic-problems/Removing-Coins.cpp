// https://www.spoj.com/problems/PALDR/en/

/*
Nesse problema a ideia é que o melhor movimento de cada jogador é pegar o ponto que esteja mais distante de todos os outros sempre, e notar que todos vao convergir para o ponto. 
Basta utilizar do diametro da arvore, pois a ideia é que como todas as moedas vao convergindo a um ponto, a melhor jogada é sempre pegar o ponto que esta mais distante de outro ponto e as moedas vao convergindo lentamente a esse ponto. (?)
Entao, feito o diametro, basta ver quantas convergencias serao necessarias para as moedas acabarem.

O padrao do jogo se repete a cada 3 dentro diametro
1 -> P 
2 -> G
3 -> G 
4 -> P
.....
*/

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

const int MAX = 200005;
const ll LINF = 0x3f3f3f3f3f3f3f3fll; 


// Centro de arvore
//
// Retorna o diametro e o(s) centro(s) da arvore
// Uma arvore tem sempre um ou dois centros e estes estao no meio do diametro
//
// O(n)

vector<int> g[MAX];
int d[MAX], par[MAX];

pair<int, vector<int>> center() {
  int f, df;
  function<void(int)> dfs = [&] (int v) {
    if (d[v] > df) f = v, df = d[v];
    for (int u : g[v]) if (u != par[v]) 
      d[u] = d[v] + 1, par[u] = v, dfs(u);
  };
 
  f = df = par[0] = -1, d[0] = 0;
  dfs(0);
  int root = f;
  f = df = par[root] = -1, d[root] = 0;
  dfs(root);
 
  vector<int> c;
  while (f != -1) {
    if (d[f] == df/2 or d[f] == (df+1)/2) c.push_back(f);
    f = par[f];
  }
 
  return {df, c};
}


signed main()
{ 
  _
  int n; cin >> n;
  n--;
  while(n--){
    int u, v; cin >> u >> v; u--;v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto ans = center();
  dbg(ans.first);
  if(ans.first % 3 == 1){
    cout << "Second" << endl;
  } else {
    cout << "First" << endl;
  }


  return 0;
}
