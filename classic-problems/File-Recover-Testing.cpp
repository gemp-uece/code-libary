// https://www.spoj.com/problems/FILRTEST/en/

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


int computeLPSArray(string &pat, int M, vector<int> &lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else{

                lps[i] = 0;
                i++;
            }
        }
    }
    return lps[M - 1]; 
}


signed main()
{ 
  _
  int n;string s;
  while(cin >> n >> s){
    if(n == -1) return 0;

    if(n < sz(s)){
      cout << 0 << endl;
      continue;
    }

    vector<int> lps(sz(s));
    int aux = computeLPSArray(s,sz(s), lps); // retorna o tamanho maior prefixo que tambem é sufixo.
    int patternLength = s.size() - aux;
    cout << 1 + (n-sz(s))/patternLength << endl;
  }


  return 0;
}
