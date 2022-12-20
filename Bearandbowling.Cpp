#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=3e5+10;
const int mod = 1e9 + 7;
int n,k,m,q,dis,lim;
ll timer=1;
long long a[sz];
long long pr[sz];
long long pf[sz];
long long dp[sz];
int pointer = 0; 
vector <long long> M;
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
int main(){
      scanf("%d",&n);
      for(int i = 1; i <= n; i++) scanf("%lld", a + i);
      for(int i = 1; i <= n; i++){
           pf[i] = pf[i - 1] + a[i];
           pr[i] = pr[i - 1] + (1ll)*a[i]*(i + 1);
      }
      long long ans = 0;
      LineContainer lc;
      for(int i = 1; i <= n; i++){
           lc.add(-i, i*pf[i - 1] - pr[i - 1]);
           ans = max(ans, pr[i] + lc.query(pf[i]));
      } 
      cout<<ans<<endl;
}
