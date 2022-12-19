#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e6+10;
const int inf=1e6+1;
int n,k,m,q,dis;
ll timer=1;
int d[sz];
long long dp[sz];
long long ds[sz];
long long pf[sz];
struct tree{
     long long wt,dis;
} a[sz];
vector <long long> M;
vector <long long> B;
bool bad(int l1,int l2,int l3)
{
        return (B[l3]-B[l1])*(M[l1]-M[l2]) < (B[l2]-B[l1])*(M[l1]-M[l3]);
}
void add(long long m,long long b)
{
        M.push_back(m);
        B.push_back(b);
        while (M.size()>=3&&bad(M.size()-3,M.size()-2,M.size()-1))
        {
                M.erase(M.end()-2);
                B.erase(B.end()-2);
        }
}
int pointer;
long long query(long long x)
{
        if (pointer >=M.size())
                pointer=M.size()-1;
        while (pointer<M.size()-1&&
          M[pointer+1]*x+B[pointer+1] >  M[pointer]*x+B[pointer])
                pointer++;
        return M[pointer]*x+B[pointer];
}
int main(){
      cin>>n;
      long long tot = 0;
      for(int i = 1; i <= n; i++){
          cin>>a[i].wt>>a[i].dis;
          ds[i + 1] = ds[i] + a[i].dis;
          pf[i] = pf[i - 1] + a[i].wt;
          tot+= (1ll)*pf[i]*a[i].dis;
      }      
      long long ans = LLONG_MAX;
      for(int i = 1; i <= n; i++){
            if(i > 1) ans = min(ans,-query(ds[i]) - ds[n+1]*pf[i] + pf[i]*ds[i] + tot);
            add(pf[i],-pf[i]*ds[i]);
      }
      cout<<ans<<endl;
}
