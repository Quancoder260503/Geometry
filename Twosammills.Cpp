#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e6+10;
const int inf=1e6+1;
int n,k,m,q,add,dis;
ll timer=1;
int d[sz];
long long dp[sz][2];
long long pf[sz];
long long pfw[sz];
long long prw[sz];
long long x[sz];
struct tree{
     long long wt,dis;
} a[sz];
bool check(int i,int j,int k){
     long long slopex = - pfw[i];
     long long slopey = - pfw[j];
     long long slopez = - pfw[k];
     long long incepx = dp[i][0] - prw[i]; 
     long long incepy = dp[j][0] - prw[j];
     long long incepz = dp[k][0] - prw[k];
     return (incepy-incepx)*(slopex-slopez) > (incepz - incepx)*(slopex - slopey);
}
int main(){
      scanf("%d",&n);
      for(int i = 1; i <= n; i++){
          scanf("%lld%lld",&a[i].wt,&a[i].dis);
      }
      for(int i = 2; i <= n + 1; i++) pf[i] = pf[i - 1] + a[i].dis;
      for(int i = 1; i <= n; i++) pfw[i] = pfw[i - 1] + a[i].wt;
      for(int i = 1; i <= n; i++) prw[i] = (1ll)*a[i].wt*prw[i - 1];
      for(int i = 1; i <= n + 1; i++) dp[i][0] = (1ll)*pf[i]*pfw[i - 1] - prw[i - 1];
      vector<long long>hull;
      hull.push_back(1);
      int ptr = 0; 
      dp[1][1] = 0; 
      for(int i = 2; i <= n; i++){
            if(ptr >= hull.size()) ptr = hull.size() - 1;
            while(ptr + 1 < hull.size()){
                 int cur = hull[ptr];
                 int nxt = hull[ptr + 1];
                 long long curval = dp[cur][0]+(1ll)*pf[i]*(pfw[i-1]-pfw[cur]) + (1ll)*(prw[i-1]-prw[cur]);
                 long long nxtval = dp[nxt][0]+(1ll)*pf[i]*(pfw[i-1]-pfw[nxt]) + (1ll)*(prw[i-1]-prw[nxt]);
                 if(curval > nxtval) ptr++;
                 else break;
            }
            int j = hull[ptr];
            dp[i][1] = dp[j][0] + (1ll)*pf[i]*(pfw[i-1]-pfw[j]) + (1ll)*(prw[i-1]-prw[j]);
            hull.push_back(i);
            while(hull.size() > 2 and check(hull[hull.size()-2],hull[hull.size()-1],hull.back())){
                    hull.erase(hull.end()- 2);
            }   
       }
       cout<<dp[3][0]<<endl;
}
