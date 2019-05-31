#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
const int MAXN = 5e4+5;
const long long INF = 0x7ffffff;
int n,q[MAXN],head=1,tail=1;
long long L,c[MAXN],sum[MAXN],dp[MAXN];
long long F(int x) {
    return (long long)(dp[x]+(sum[x]+L+1)*(sum[x]+L+1));
}
long long G(int x) {
    return (long long)(sum[x]);
}
double K(int x) {
    return (double)((sum[x])*2);
}
double GetK(int x,int y) {
    if(x==y)    return 0;
    return (double)(F(x)-F(y))/(double)(G(x)-G(y));
}

int main() {  
    scanf("%d%lld",&n,&L);
    for(int i=1;i<=n;i++) {
        scanf("%lld",&c[i]);
        sum[i]=sum[i-1]+c[i]+1;
    }
    for(int i=1;i<=n;i++) {
        while(head<tail && GetK(q[head],q[head+1]) <= K(i))    head++;
        dp[i]=dp[q[head]]+(sum[i]-sum[q[head]]-L-1)*(sum[i]-sum[q[head]]-L-1);
        while(head<tail && GetK(q[tail],q[tail-1]) > GetK(i,q[tail])) tail--;
        q[++tail]=i;
    }
    printf("%lld\n",dp[n]);
    return 0;
}