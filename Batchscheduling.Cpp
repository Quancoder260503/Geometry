#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=3e5+10;
const int mod = 1e9 + 7;
int n,k,m,q,dis,lim;
ll timer=1;
long long pr[sz];
long long pf[sz];
long long pt[sz];
long long dp[sz];
struct job{
    long long t,f; 
} a[sz];
vector <long long> M;
vector <long long> B;
bool bad(int l1,int l2,int l3)
{
        return (B[l3]-B[l1])*(M[l1]-M[l2])<(B[l2]-B[l1])*(M[l1]-M[l3]);
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
          M[pointer+1]*x+B[pointer+1]>M[pointer]*x+B[pointer])
                pointer++;
        return M[pointer]*x+B[pointer];
}
int main(){
      scanf("%d",&n);
      scanf("%d",&k);
      for(int i = 1; i <= n; i++){
           scanf("%lld%lld",&a[i].t,&a[i].f);
      }
      for(int i = n; i > 0; i--){
           pf[i] = pf[i + 1] + a[i].f;
           pt[i] = pt[i + 1] + a[i].t;
      }
      add(0,0);
      for(int i = n; i > 0; i--){
            dp[i] =  (1ll)*k*pf[i] - query(pf[i]) + (1ll)*pf[i] * pt[i];
            add(pt[i],-dp[i]);
      }
      cout<<dp[1]<<endl;
}
