#include<bits/stdc++.h>

using namespace std;
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>Ordered_set;
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

typedef long long int              ll;
typedef vector<int>                vi;
typedef vector<ll>                 vl;
typedef vector<vector<int>>        vvi;
typedef pair<int, int>             pi;
typedef vector<pair<int, int>>      vpi;
typedef vector<pair<ll, ll>>        vpl;

#define sz(x)                      ((int)(x).size()) //never forget to type into int
#define inp(a, n)                  for(int Ele=0; Ele<(n); Ele++)cin>>a[Ele]
#define inp1(a, n)                 for(int Ele=1; Ele<=(n); Ele++)cin>>a[Ele]
#define set_bits(n)                __builtin_popcountll(n)
#define max(a, b)                  (a < b ? b : a)
#define min(a, b)                  ((a > b) ? b : a)

#define INF                        1e18
#define kick(x)                    cout << "Case #" << x << ": ";
#define lb                         lower_bound
#define ub                         upper_bound
#define min_element                *min_element
#define max_element                *max_element
#define pb                         push_back
#define ppb                        pop_back
#define mp                         make_pair
#define rr return

//#define mod                       (in1e9+7
#define ff                        first
#define ss                        second
#define ceil(x,a)                 ((x + a - 1)/(a))
#define all(v)                    v.begin(), v.end()

ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}


bool sortbysec(const pair<int, int> &a, const pair<int, int> &b) {return (a.second < b.second);}
//Prime_Seive
//bool prime[1000000+9]; void seive(){ ll N=1e6+1; memset(prime,true,sizeof(prime)); prime[0]=false; prime[1]=false; for(ll i=2;i*i<=N;i++){ if(prime[i]){ for(ll j=i*i;j<=N;j+=i){ prime[j]=false;}}}}
// check whether the given number is pow of 2
bool isPowerOfTwo(ll x) {return (x && !(x & (x - 1)));}


bool is_prime(ll n) {if (n <= 1)return false; if (n <= 3)return true; if (n % 2 == 0 || n % 3 == 0)return false; for (int i = 5; i * i <= n; i = i + 6)if (n % i == 0 || n % (i + 2) == 0)return false; return true;}
int   dx[4] = {1, -1, 0, 0};
int   dy[4] = {0, 0, -1, 1};

class DSU {
public:
   int N;
   vl par;


   DSU(int m) {
      N = m;
      par.assign(m + 1, 0);
      for (int i = 0; i <= m; i++)par[i] = i;
   }

   int find_par(int node) {
      if (node == par[node])return node;
      return par[node] = find_par(par[node]);
   }

   void merge(int node1, int node2) {
      int a = find_par(node1);
      int b = find_par(node2);
      if (a != b)par[a] = b;
   }
};



bool allSubstring(vector<char> v) {
   map<string, int> mp;
   for (int i = 0; i < v.size(); i++) {
      string str = "";
      for (int j = i; j < v.size(); j++) {
         str += v[j];
         mp[str]++;
      }
   }
   for (auto it : mp) {
      if (it.ss % 2 == 0) {
         return 0;
      }
   }
   return 1;
}
vector<char> v;
void helper(int i, int n) {
   if (i == n) {
      if (allSubstring(v)) {
         for (auto it : v)cout << it;
         cout << "\n";
         exit(1);
      }
      return ;
   }

   for (char ch = 'a'; ch <= 'z'; ch++) {
      v.pb(ch);
      helper(i + 1, n);
      v.pop_back();
   }
}

void floydWarshall(vector<vector<int>> &dist, int n)
{
   int  i, j, k;
   for (k = 0; k < n; k++) {
      for (i = 0; i < n; i++) {
         for (j = 0; j < n; j++) {
            if (dist[i][j] > (dist[i][k] + dist[k][j])
                  && (dist[k][j] != INT_MAX
                      && dist[i][k] != INT_MAX))
               dist[i][j] = dist[i][k] + dist[k][j];
         }
      }
   }
}




int main() {
#ifndef ONLINE_JUDGE
   freopen("input1.txt", "r", stdin);
   freopen("output1.txt", "w", stdout);
#endif
   fast_io

   int t;
   cin >> t;
   for (int i = 0; i < t; i++) {
      string s; cin >> s;
      int e; cin >> e;
      unordered_map<char, vector<char>> m;
      unordered_set<char> tmp;
      for (int j = 0; j < e; j++) {
         string ed; cin >> ed;
         m[ed[0]].push_back(ed[1]);
         tmp.insert(ed[0]);
         tmp.insert(ed[1]);
      }
      for (char ch : s) {
         tmp.insert(ch);
      }
      int n = tmp.size(), ind = 0;
      unordered_map<char, int> nodes;
      for (char ch : tmp) {
         nodes[ch] = ind++;
      }
      vector<vector<int>> g(n, vector<int>(n, INT_MAX));
      for (int i = 0; i < n; i++)g[i][i] = 0;
      for (auto itr : m) {
         for (auto k : itr.second) {
            g[nodes[itr.first]][nodes[k]] = 1;
         }
      }
      floydWarshall(g, n);
      int res = INT_MAX;
      for (char ch : tmp) {
         int cnt = 0;
         bool dis = false;
         for (char c : s) {
            int dist = g[nodes[c]][nodes[ch]];
            if (dist == INT_MAX) {
               dis = true;
               break;
            }
            cnt += dist;
         }
         if (dis)continue;
         res = min(res, cnt);
      }
      cout << "Case #" << i + 1 << ": ";
      if (res == INT_MAX)cout << -1 << endl;
      else cout << res << endl;

   }
   return 0;
}
