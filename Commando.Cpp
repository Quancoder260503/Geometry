#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e6+10;
const int inf=1e6+1;
int n,k,m,q,add,dis;
ll timer=1;
int d[sz];
long long a,b,c;
long long dp[sz];
long long pf[sz];
long long x[sz];
long double slope(int i, int j){
        long long slopex = -(1ll)*2*pf[i];
        long long slopey = -(1ll)*2*pf[j];
        long long incepx = dp[i] + (1ll)*a*pf[i]*pf[i] - (1ll)*b*pf[i];
        long long incepy = dp[j] + (1ll)*a*pf[j]*pf[j] - (1ll)*b*pf[j];
        return (long double) (incepx - incepy)/ (slopex - slopey);
}
int main(){
       iostream::sync_with_stdio(false);
	     cin.tie(0);
       scanf("%d",&n);
       scanf("%lld%lld%lld",&a,&b,&c);
       deque<int>hull{0};
       for(int i = 1; i <= n; i++) scanf("%lld", x + i);
       for(int i = 1; i <= n; i++) pf[i] = pf[i - 1] + x[i];
       int ptr = 0;
       for(int i = 1; i <= n; i++){
            if(ptr > hull.size()) ptr = hull.size() - 1;
            while(ptr + 1 < hull.size()){
                int cur = hull[ptr];
                int nxt = hull[ptr + 1];
                //if(i == 3) cout<<cur<<' '<<nxt<<endl;
                long long curval = dp[cur]+(1ll)*a*pf[cur]*pf[cur]-(1ll)*b*pf[cur]-2*(1ll)*a*pf[i]*pf[cur];
                long long nxtval = dp[nxt]+(1ll)*a*pf[nxt]*pf[nxt]-(1ll)*b*pf[nxt]-2*(1ll)*a*pf[i]*pf[nxt];
                if(curval < nxtval) ptr++;
                else break;
            }
            int j = hull[ptr];
            dp[i] = (1ll)*a*pf[i]*pf[i] + (1ll)*b*pf[i] + c;
            dp[i] = dp[i] + dp[j] + (1ll)*a*pf[j]*pf[j] - (1ll)*b*pf[j] - 2*(1ll)*a*pf[i]*pf[j];
            while(hull.size() > 1 and slope(hull[hull.size()-2],hull.back()) >= slope(hull.back(),i)){
                  hull.pop_back();
            }
            hull.push_back(i);
       }
       cout<<dp[n]<<endl;
}
