#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;
const long long INF = 0x7fffffffffff;
int n,x[20],y[20],s;
long long dp[20][1<<18];
int main() {    
    scanf("%d%d",&n,&s);
    for(int i=0;i<n;i++) {
        scanf("%d%d",&x[i],&y[i]);
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<(1<<n);j++) {
            dp[i][j]=INF;
        }
    }
    dp[s-1][1<<(s-1)]=0;
    for(int S=0;S<(1<<n);S++) {
        for(int i=0;i<n;i++) {
            if(S & (1<<i)) {
                for(int j=0;j<n;j++) {
                    long long dis=abs(x[i]-x[j])+abs(y[i]-y[j]);
                    if(!(S & (1<<j)))
                        dp[j][S | (1<<j)]=min(dp[j][S | (1<<j)],dp[i][S]+dis);
                }
            }
        }
    }
    long long ans=INF;
    for(int i=0;i<n;i++) {
        ans=min(ans,dp[i][(1<<n)-1]);
    }
    printf("%lld\n",ans);
    return 0;
}