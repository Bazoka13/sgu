#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define N 1001
int pri[N];
vector<int> dp[N][N/10];
const int mod=1000000000;
void add(vector<int> &a,vector<int> &b)
{
  int c=0;
  int i=0;
  for(;i<b.size();++i)
    {
      if(i<a.size())
	c+=a[i];
      c+=b[i];
      if(i<a.size())
	a[i]=c%mod;
      else a.push_back(c%mod);
      c/=mod;
    }
  for(;i<a.size() && c;++i)
    {
      c+=a[i];
      a[i]=c%mod;
      c/=mod;
    }
  if(c)
    a.push_back(c);
}
void pt(vector<int> &a)
{
  if(a.size()==0)
    printf("0");
  else
    {
      int i=a.size()-1;
      printf("%d",a[i]);
      for(--i;i>=0;--i)
	printf("%09d",a[i]);
    }
}
int main()
{
  for(int i=2;i<N;++i)
    if(pri[i]==0)
      {
	for(int j=i*i;j<N;j+=i)
	  pri[j]=1;
	vector<int> ans;
	dp[0][0].push_back(1);
	for(int j=1;j<=2*i;++j)
	  for(int l=min(j,i)-1;l>=max(0,i-(2*i-j+1));--l)
	    for(int k=0;k<i;++k)
	      if(dp[k][l].size()>0)
		add(dp[(k+j)%i][l+1],dp[k][l]);
	cout<<"p["<<i<<"]=(string)\"";
	pt(dp[0][i]);
	cout<<"\";"<<endl;
	for(int j=0;j<i;++j)
	  for(int k=0;k<=i;++k)
	    dp[j][k].resize(0);
      }
  return 0;
}
