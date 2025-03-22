#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int long long
#define pii pair<int,int>
#define ld long double
#define isPower2(a) (a == 0 ? false : ((a & (a - 1)) == 0 ? true : false))
#define isEven(a) ((a & 1) == 0 ? true : false)
// Check if the kth bit (from right -> left) is set ( Ex: (8,1) -> false || (7,1) -> true)
#define checkKBit(a, k) ((a & (1 << k)) != 0 ? true : false)
#define setKBit(a, k) (a | (1 << k))
#define unsetKBit(a, k) (a & ~(1 << k))
#define toggleKBit(a, k) (a ^ (1 << k))
#define divideByPower2(a, k) (a >> k)
#define moduloByPower2(a, k) ((a & ((1 << k) - 1)))
#define multiplyByPower2(a, k) (a << k)
#define getNumberOfSetBits(a) (__builtin_popcountll(a))
#define getNumberOfLeadingZeros(a) (__builtin_clzll(a))
#define xorOp(a, b) (a ^ b)
#define swap(a, b) \
    {              \
        a = a ^ b; \
        b = a ^ b; \
        a = a ^ b; \
    }
// if x == a -> x = b else if x == b -> x = a
#define swapConditional(a, b, x) {a ^ b ^ x}

#define yes() cout << "YES" << endl;
#define no() cout << "NO" << endl;

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const long long MOD = 998244353;

const int maxn = 1e3;

int m_menor = INF;
int m_maior = -(INF-1); 
int minPos = -1, maxPos = -1;

template<typename T> void rep(vector<T> &v){
    for(int i = 0; i < v.size(); i++){
        cin >> v[i];
    }
    maxPos = max_element(v.begin(), v.end()) - v.begin();
    minPos = min_element(v.begin(), v.end()) - v.begin();
}

template<typename T> void rep_graph(vector<vector<T>> &graph, int m,bool directed = false){
    for(int i = 0; i < m; i++){
        int u,v; cin >> u >> v; 
        graph[u].push_back(v); if(!directed) {graph[v].push_back(u);}
    }
}  

template<typename T>
void print_vector(const vector<T>& v, string id = "id: ", string value = "va: ") {
    if (v.empty()) return;

    int max_index_digits = to_string(v.size() - 1).size();
    int max_value_digits = 1;

    for (const auto& val : v) {
        max_value_digits = max(max_value_digits, (int)to_string(val).size());
    }

    int width = max(max_index_digits, max_value_digits) + 1; 

    cout << id;
    for (int i = 0; i < v.size(); i++) {
        cout << setw(width) << i << " ";
    }
    cout << endl;

    cout << value;
    for (const auto& val : v) {
        cout << setw(width) << val << " ";
    }
    cout << endl;
}

pair<int,int> fraction(int a, int b){
    for(int i = max(a,b); i > 1; i--){
        if(a % i == 0 && b % i == 0){
            return fraction(a/i, b/i);

        }
    }
    return {a,b};
}

vector<int> z(string pat, string s){
    string concat = pat + "$" + s;
    int n = concat.size();
    vector<int> zArr(n, 0);
    for(int i = 1; i < n; i++){
        int l,r; 
        l = 0; r = i;
        while(concat[l] == concat[r]){
            zArr[i]++;
            if(r > i) {
                zArr[r] = zArr[l];
            }
            l++;
            r++;
        }
        if(zArr[i] != 0){
            i = i + zArr[i] - 1;
        }   
    }
    return zArr;
}

void remove(string &s, int &count){
    s.pop_back();
    count++;
}

void dfs(int u,vector<vector<int>> &graph,vector<int> &visited){
    visited[u] = true;
    for(auto v : graph[u]){
        if(visited[v]) continue;
        dfs(v, graph, visited);
    }
}

bool testes_allowed = false;
int solve(int n){
    /**
     * dado n cidade e m estradas que ligam as cidades
     * o objetivo é construir novas estradas entre cada cidadde
     * sua tarefa é achar o menor numero de estradas necessárias
     * 
     * 
     * a ideia é rodar uma dfs no grafo, encontrar os componentes desconexos e printar par a par
     * entre as cidades.
     **/

    int m; cin >> n >> m;
    vector<vector<int>> graph(n+5);rep_graph(graph,m);
    vector<int> visited(n+5, 0);
    vector<int> components;
    for(int u = 1; u <= n; u++){
        if(visited[u]) continue;
        components.push_back(u);
        dfs(u,graph,visited);
    }
    cout << components.size() - 1 << endl;
    for(int i = 1; i < components.size(); i++){
        cout << components[i-1] << " " << components[i] << endl;
    } 

    return 0;
}

signed main() { _
    int t = 1; 
    if(testes_allowed) cin >> t;
    while(t--){
        int x = 0;
        // int x; cin >> x;
        solve(x);
    }
    exit(0);
}