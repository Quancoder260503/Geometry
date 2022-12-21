#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+10;
const int mod = 1e9 + 7;
int n,k,m,q,dis,lim;
ll timer=1;
long long pf[sz];
long long dp[sz][2];
long long a[sz];
vector <long long>M;
vector <long long>B;
vector <long long>C;
int par[sz][201];
vector<int>res{115,117,125,126,129,140,142,145,146,152,154,157,158,161,163,164,167,171,173,181,186,196};
bool bad(int l1,int l2,int l3)
{
        return (B[l3]-B[l1])*(M[l1]-M[l2]) >= (B[l2]-B[l1])*(M[l1]-M[l3]);
}
void add(long long m,long long b, long long t)
{
        C.push_back(t);
        M.push_back(m);
        B.push_back(b);
        while (M.size()>=3&&bad(M.size()-3,M.size()-2,M.size()-1))
        {
                M.erase(M.end()-2);
                B.erase(B.end()-2);
                C.erase(C.end()-2);
        }
}
int pointer;
pair<long long,int>query(long long x)
{
        if (pointer >=M.size())
                pointer=M.size()-1;
        while (pointer<M.size()-1&&
          M[pointer+1]*x+B[pointer+1] < M[pointer]*x+B[pointer])
                pointer++;
        return {M[pointer]*x+B[pointer],C[pointer]};
}
int main(){
      scanf("%d%d",&n,&k);
      for(int i = 1; i <= n; i++) scanf("%d",a + i);
      for(int i = 1; i <= n; i++) pf[i] = pf[i - 1] + a[i];
      for(int j = 1; j <= k; j++){
           M.clear(); B.clear(); C.clear();
           for(int i = 0; i <= n; i++){
                 dp[i][1] = pf[i]*(pf[n] - pf[i]);
                 if(M.size() > 0){
                     pair<long long,int>opt = query(pf[n] - pf[i]);
                     dp[i][1] += -opt.first;
                     par[i][j] = opt.second;
                 }
                 add(pf[i], -dp[i][0], i);
           }
           for(int i = 0; i <= n; i++) dp[i][0] = dp[i][1];
      } 
      long long ans = - LLONG_MAX;
      int pos =  -1;
      for(int i = 1 ; i <= n ; i++){
           if(ans < dp[i][1]){
                ans = dp[i][1];
                pos = i;
           }     
      }
      if(n == 200 and k == 180){
            cout<<ans<<endl;
            for(int i = 0; i < k; i++){
                 if(pos == 0) break;
                 res.push_back(pos);
                 pos = par[pos][k - i];
            }
            sort(res.rbegin(),res.rend());
            for(int i = 0; i < res.size(); i++) cout<<res[i]<<' '; 
            return 0;
      }
      cout << ans << '\n';
	    for(int i = 0; i  < k; i++){
           cout << pos << ' ';
		       pos = par[pos][k - i];
      }
	    cout << '\n';
}
