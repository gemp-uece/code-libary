// https://www.spoj.com/problems/ACTIV/en/

/*
Ideia : Dado que temos um conjunto - Temos N classes, cada uma com intervalo [S, E).

Queremos contar **quantos subconjuntos não vazios** de classes são formados por atividades que **não se sobrepõem**.
Se uma atividade termina exatamente quando outra começa, elas **não se sobrepõem**.

Solução:
- Ordenar as atividades pelo tempo de termino(E).
- Para cada atividade i, encontrar a ultima atividade j que termina antes ou exatamente no inicio da atividade i(ou seja, v[j].ft <= v[i].sd)
- Usamos DP para contar o numero de subconjuntos validos
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

const int MAX = 2e5+5;
const ll LINF = 0x3f3f3f3f3f3f3f3fll; 
const int MOD = 1e8;


signed main()
{ 
  _
  int n;
  while(cin >> n){
    if(n == -1) return 0;
    vector<pair<int,int>> v;
    v.push_back({0,0});
    for(int i = 0; i < n; i++){
      int a,b; cin >> a >> b;
      v.push_back({b,a}); // y , x
    }
    sort(v.begin(),v.end());
    vector<int> dp(MAX,0);
    for(int i = 1; i <= n; i++){
      int l = 0, r = i-1, mx = 0;
      while(l <= r){
        int md = (l+r)/2;
        if(v[md].first <= v[i].second){ // mx é
          // o maior indice tal que a atividade mx termina antes
          // do inicio da atividade i.
          l = md + 1;
          mx = max(mx,md);
        } else r = md - 1;
      }
      // `dp[i]` representa o número de subconjuntos não vazios formados pelas primeiras i atividades ordenadas.
      // dp[i] = dp[mx] + 1 ( quantos formo com o i) e dp[i-1] quantos formo sem i, imaginar o passo recursivo. 
      dp[i] = dp[mx] + 1 + dp[i-1];
      dp[i] %= MOD;
    }

    printf("%08lld\n", dp[n]);
  }

  return 0;
}
