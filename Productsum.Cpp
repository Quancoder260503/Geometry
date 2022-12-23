#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 2e5+10;
const int mod = 1e9 + 7;
int n,k,m,q,dis,lim;
ll timer=1;
long long pf[sz];
long long pr[sz];
long long a[sz];
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
     long long tot = 0;
     for(int i = 1; i <= n; i++) cin>>a[i];
     for(int i = 1; i <= n; i++) tot += a[i]*i;
     for(int i = 1; i <= n; i++) pf[i] = pf[i - 1] + a[i];
     long long ans = tot;
     LineContainer lc; 
     lc.add(0,0);
     for(int i = 1; i <= n; i++){
           ans = max(ans, tot + pf[i] + lc.query(a[i]) - a[i]*i);
           lc.add(i, -pf[i]);
     }
     LineContainer lc1;
     lc1.add(0,0);
     for(int i = n; i > 0; i--){
           ans = max(ans, tot + pf[i] + lc1.query(a[i]) - a[i]*i);
           lc1.add(i,-pf[i]);
     }
     cout<<ans<<endl;
}
