
 #include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+10;
const int mod = 1e9 + 7;
int n,k,m,q,dis,lim;
ll timer=1;
long long trs[sz];
long long a[sz];
long long b[sz];
bool huge[sz];
long long dp[sz];
vector<int> adj[sz];
bool _Line_Comp_State; 
struct Line {
	// k is slope, m is intercept, p is intersection point
	mutable long long k, m, p;
	bool operator<(const Line& o) const {
		return _Line_Comp_State ? p < o.p : k < o.k;
	}
};
 
struct LineContainer : multiset<Line> {
	long long div(long long a, long long b) { return a / b - ((a ^ b) < 0 && a % b); }
 
	bool isect(iterator x, iterator y) {
		if (y == end()) { 
			x->p = LLONG_MAX; 
			return false; 
		}
		if (x->k == y->k) {
			x->p = x->m > y->m ? LLONG_MAX : -LLONG_MAX;
		} else {
			x->p = div(y->m - x->m, x->k - y->k);
		}
		return x->p >= y->p;
	}
	void add(long long k, long long m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) {
			z = erase(z);
		}
		if (x != begin() && isect(--x, y)) {
			isect(x, y = erase(y));
		}
		while ((y = x) != begin() && (--x)->p >= y->p) {
			isect(x, erase(y));
		}
	}
 
	long long query(long long x) {
		assert(!empty());
		_Line_Comp_State = 1; 
		auto l = *lower_bound({0, 0, x}); 
		_Line_Comp_State = 0;
		return l.k * x + l.m;
	}
};
void dfs(int u,int p){
     trs[u] = 1;
     for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i];
         if(v == p) continue;
         dfs(v,u);
         trs[u] += trs[v];
     }
}
void dfs_hld(int u,int p, LineContainer &lines){
      int mx = -1;
      int big = -1;
      for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v == p) continue;
            if(mx < trs[v]){
               mx = trs[v];
               big = v;
            }
      }
      if(big != - 1) dfs_hld(big,u,lines);
      for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v == p or v == big) continue;
            LineContainer extract;
            dfs_hld(v,u,extract);
            for(auto it: extract) lines.add(it.k,it.m);
      }
      if(big != -1) dp[u] = -lines.query(a[u]);
      else dp[u] = 0;
      lines.add(-b[u],-dp[u]);
}
int main(){
     cin>>n;
     for(int i = 1; i <= n; i++) cin>>a[i];
     for(int i = 1; i <= n; i++) cin>>b[i];
     for(int i = 1; i < n; i++){
          int u,v; cin>>u>>v;
          adj[u].push_back(v);
          adj[v].push_back(u);
     }
     memset(dp,0x3f,sizeof(dp));
     dfs(1,0);
     LineContainer lc;
     dfs_hld(1,0,lc);
     for(int i = 1; i <= n; i++) cout<<dp[i]<<' ';
}
