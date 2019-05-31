#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
#define int long long
using namespace std;
const int MAXN = 5005;  
const long long INF = 0x7ffffffffffffff;
struct node {
    long long val,cost,charm;
    bool operator < (const node &w) const {
        return charm < w.charm;
    }
}gorgeous[MAXN];
long long n,m,k,x,y,dp[MAXN][MAXN];
signed main() {    
    scanf("%lld%lld%lld%lld%lld",&n,&m,&k,&x,&y);
    for(int i=1;i<=n;i++) {
        long long a,b,c,d;
        scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
        gorgeous[i].val=a;
        if(b>c) gorgeous[i].cost=0;
        else    gorgeous[i].cost=(c-b)*y;
        gorgeous[i].charm=d;
    }
    sort(gorgeous+1,gorgeous+1+n);
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++) {
        for(int j=0;j<=m;j++) {
            dp[i][j]=max(dp[i][j],dp[i-1][j]);
            if((j==0 || dp[i-1][j]) && j+gorgeous[i].cost<=m) {
                dp[i][j+gorgeous[i].cost]=max(dp[i][j+gorgeous[i].cost],dp[i-1][j]+gorgeous[i].val);
            }
        }
    }

//    for(int i=1;i<=n;i++)   cout<<gorgeous[i].val<<' '<<gorgeous[i].cost<<' '<<gorgeous[i].charm<<endl;
 //   cout<<dp[1][5]<<' '<<dp[2][5]<<endl;
    long long ans=0;
    for(int i=k;i<=k+m;i++) {
        int pos=upper_bound(gorgeous+1,gorgeous+1+n,(node){0,0,i})-gorgeous-1;
        long long maxn=0,temp=m-(i-k)*x;
        if(temp<0)  break;
//        cout<<pos<<'~'<<temp<<' ';
        for(int j=temp;j>=0;j--) {
            maxn=max(maxn,dp[pos][j]);
        }
//        cout<<maxn<<endl;
        ans=max(ans,maxn);
    }
    printf("%lld\n",ans);
    return 0;
}
/*
5 11 0 2 1

3 1 3 2
5 2 4 3
9 0 5 1
2 3 4 5
2 2 4 1
*/