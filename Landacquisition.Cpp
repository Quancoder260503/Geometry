#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=3e5+10;
const int MAXN = 3e5 + 10;
long long ans[sz];
int n;
int ptr = 0;
long long dp[sz];
vector<array<long long,3>>queries;
long long tree[MAXN<<2];
struct point{
    long long x,y;
    bool operator<(point B){
         //if(x == B.x) return y < B.y;
         return x < B.x;
    }
} a[sz];
vector<long long>slope;
vector<long long>incep;
point rec[sz];
bool check(int i, int j, int k){
     return (long long) (incep[j]-incep[i])*(slope[i]-slope[k])>(incep[k] - incep[i])*(slope[i] - slope[j]);
}
long long query(long long xcor){
      if(ptr >= slope.size()) ptr = slope.size() - 1;
      while(ptr + 1 < slope.size()){
           if((1ll)*(slope[ptr]*xcor + incep[ptr]) > (1ll)*(slope[ptr + 1]*xcor + incep[ptr + 1])) ptr++;
           else break;
      }
      return (1ll)*(slope[ptr]*xcor) + incep[ptr];
}
int main(){
     cin>>n;
     for(int i = 0; i < n; i++){
          cin>>a[i].x>>a[i].y;
     }    
     sort(a, a + n);
     int m = 0;
     for(int i = 0; i < n; i++){
          while( m > 0 and rec[m - 1].y <= a[i].y) m--;
          rec[m++] = a[i];
     }
     incep.push_back(0);
     slope.push_back(rec[0].y);
     for(int i = 0; i < m; i++){
          dp[i] = query(rec[i].x);
          if(i < m - 1){
               slope.push_back(rec[i + 1].y);
               incep.push_back(dp[i]);
               int cur = slope.size();
               while(slope.size() > 2 and check(cur-3,cur-2,cur-1)){
                      slope.erase(slope.end()-2);
                      incep.erase(incep.end()-2);
                      cur = slope.size();
               }
          }
     } 
     cout<<dp[m - 1]<<endl;
}
