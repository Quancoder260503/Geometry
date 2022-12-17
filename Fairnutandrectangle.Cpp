#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e6+10;
const int inf=1e6+1;
int n,k,m,q,add,dis;
ll timer=1;
int d[sz];
struct rect{
    long long x,y,val;
    bool operator<(rect B){ return x < B.x ;}
} a[sz];
long long dp[sz];
long double slope(int i, int j){
     return (long double) (dp[i] - dp[j]) / (a[i].x - a[j].x);
}
int main(){
       iostream::sync_with_stdio(false);
	     cin.tie(0);
       cin>>n;
       for(int i = 1; i <= n; i++){
             cin>>a[i].x>>a[i].y>>a[i].val;    
       }
       sort(a + 1, a + n + 1);
       deque<int>q;
       q.push_back(0);
       for(int i = 1; i <= n; i++){
            while(q.size() > 1 and slope(q[0],q[1]) >= a[i].y) q.pop_front(); 
            int j = q.front();
            dp[i] = max(dp[i - 1], a[i].x*a[i].y - a[i].val -(a[j].x * a[i].y) + dp[j]);
            while(q.size() > 1 and slope(q[q.size()-2],q.back()) <= slope(q.back(),i)) q.pop_back();
            q.push_back(i);
       }
       cout<<dp[n]<<endl;
}
