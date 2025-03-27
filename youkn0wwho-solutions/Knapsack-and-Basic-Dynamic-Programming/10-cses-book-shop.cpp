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

bool testes_allowed = false;
int solve(int n){
    /**
     * dado n items, de valor vi e capacidade wi
     * e dado uma capacidade maxima W.
     * qual o maior valor de itens que consigo colocar na mochila sem
     * exceeder a capacidade total
     * 
     * I) f[i][j] = estado que carrego o maior valor com uma capacidade j usando apenas os primeiros i itens.
     * II) Se eu nao colocar o item na mochila -> f[i-1][j]
     * III) Se eu colocar o item na mochila -> f[i-1][j - wi] + vi
     * IV) f[i][j] = max(f[i-1][j], f[i-1][j - wi] + vi)
     * 
     * V) podemos reduzir uma dimensao se fizermos a transição ocorrer de maneira 
     * decrescente de j:
     * f[j] = max(f[j], f[j-w] + vi);
     * 
     * isso acontece por que : 
     * temos o exemplo construido a de baixo pra cima.
     * id:   0   1   2   3   4   5   6   7   8   9  10 
     * va:   0   0   0   0   5   5   5   5  10  10  10 
     * 
     * de cima pra baixo: (esse é o correto)
     * id:   0   1   2   3   4   5   6   7   8   9  10 
     * va:   0   0   0   0   5   5   5   5   5   5   5 
     * 
     * e qual pode ser o problema ocasionado ? 
     * estamos calculando no f[10] do primeiro caso como se estivessemos colocando o mesmo item 2 vezes. 
     * nao so esse problema, mas o calculo de f[10] esta sendo impactado pelo f[5] ambos tratando do mesmo item.
     * 
     * 
     * 
     * 
     * */
    cin >> n; int x; cin >> x;
    vector<int> prices(n), pages(n), f(x+1, 0); rep(prices); rep(pages);
    for(int i = 0; i < n; i++){
        for(int j = prices[i]; j <= x; j++){
            f[j] = max(f[j], f[j-prices[i]] + pages[i]);
        }
        print_vector(f);
        cout << endl;
    }

    cout << f[x] << endl;
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