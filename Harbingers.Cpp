#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+10;
const int mod = 1e9 + 7;
typedef pair<long long,long long>info;
int n,k,m,q,dis,lim;
ll timer=1;
long long d[sz];
long long dp[sz];
vector<pair<long long,long long>>adj[sz];
pair<long long,long long>lines[sz];
vector<pair<info,info>>lst;
struct harbinger{
    long long s,v;
}a[sz];
long long query(long long x){
      int l = 0; int r = lim - 1;
      long long ans = lines[0].first*x + lines[0].second;
      while(l < r){
           int mid = (l + r)>>1;
           long long lval = lines[mid].first*x + lines[mid].second;
           long long rval = lines[mid + 1].first*x + lines[mid + 1].second;
           if(lval >= rval) l = mid +1;
           else r = mid;
           ans = min(ans,min(lval,rval));
      }
      return ans;
}
bool check(info &a,info &b,info &c){
      long double x = (long double)(b.second - a.second)/(a.first - b.first);
      long double y = (long double)(c.second - a.second)/(a.first - c.first);
      return (x >= y); 
}
void add_line(info line){
     int l = 1; int r = lim - 1; int k = lim;
     while(l <= r){
          int mid = (l + r)>>1;
          if(check(lines[mid - 1],lines[mid],line)){
               r = mid - 1;
               k = mid;
          }
          else l = mid + 1;
     }
     lst.push_back({{k,lim},lines[k]});
     lines[k] = line;
     lim = k + 1; 
}
void dfs(int u,int p){
     dp[u] = (1ll)*a[u].v*d[u] + a[u].s + query(a[u].v);
     add_line(make_pair(-d[u],dp[u]));
     for(int i = 0; i < adj[u].size(); i++){
          pair<long long,long long>v = adj[u][i];
          if(v.first == p) continue;
          d[v.first] = d[u] + v.second;
          dfs(v.first,u);
     }
     pair<info,info>cur = lst.back();
     lst.pop_back();
     lines[cur.first.first] = cur.second;
     lim = cur.first.second;    
}
int main(){
      scanf("%d",&n);
      for(int i = 1; i < n; i++){
           long long u,v,w; scanf("%lld%lld%lld",&u,&v,&w);
           adj[u].push_back({v,w});
           adj[v].push_back({u,w});
      }
      for(int i = 2; i <= n; i++){
          scanf("%lld%lld",&a[i].s,&a[i].v);   
      }
      dfs(1,0);
      for(int i = 2; i <= n; i++) cout<<dp[i]<<' ';
