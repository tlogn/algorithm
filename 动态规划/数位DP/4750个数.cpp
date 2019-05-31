#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
const int MAXN = 1e5+5;
const long long INF = 0x7ffffff;
const long long mod = 0xff0000;
char st1[MAXN],st2[MAXN];
int len1,len2,p[5]={0,4,7,5,0};
long long dp[MAXN][5],pre[MAXN],PRE[MAXN];
//
long long dfs(char *st,int pos,int op,bool limit,int len) {

    if(pos>len)  return op==4;

    if(!limit && dp[pos][op]!=-1)   return dp[pos][op];

//    cout<<(int)st[pos]<<' ';

    long long ret= (op==4);
    int OP=op;
//    if(op==4)   cout<<pos<<endl;
    if(op==4)   op=0;
    if(!limit)  ret=(ret*pre[pos])%mod;
    else    ret=(ret*PRE[pos])%mod;

    int UP= limit ? st[pos] : 9;
    for(int i=0;i<=UP;i++) {
        if(p[op+1]==i) {
            ret=(ret+dfs(st,pos+1,op+1,limit && i==st[pos],len))%mod;
        //    cout<<dfs(st,pos+1,op+1,limit && i==st[pos],len)<<' ';
        }
        else {
            if(i==4) {
            //if(op!=0)  
                ret=(ret+dfs(st,pos+1,1,limit && i==st[pos],len))%mod;
            }
            else ret=(ret+dfs(st,pos+1,0,limit && i==st[pos],len))%mod;
        }
    }

    if(!limit)  dp[pos][OP]=ret%mod;
    return ret%mod;
}
long long solve(char *st,int len) {
//    for(int i=1;i<=len;i++) cout<<(int)st[i];
//    cout<<endl;
    memset(dp,-1,sizeof(dp));
    pre[len+1]=1;
    for(int i=len;i>=1;i--) {
        pre[i]=(pre[i+1]*10)%mod;
    }

    PRE[len+1]=0;
    for(int i=len;i>=1;i--) {
        PRE[i]=(PRE[i+1]+(st[i]*pre[i+1])%mod)%mod;
    }
    for(int i=1;i<=len;i++) PRE[i]=(PRE[i]+1)%mod;
    return dfs(st,1,0,1,len);
}
int main() { 
    scanf("%s%s",st1+1,st2+1);
//    cin>>st2+1;
    len1=strlen(st1+1);
    len2=strlen(st2+1);
    for(int i=1;i<=len1;i++)    st1[i]-='0';
    for(int i=1;i<=len2;i++)    st2[i]-='0';
    
    st1[len1]--;
    for(int i=len1;i>=1;i--) {
        if(st1[i]>=0)   break;
        st1[i]+=10;
        st1[i-1]--;
    }
    if(st1[1]==0) {
        for(int i=1;i<=len1;i++)    st1[i]=st1[i+1];
        len1--;
    }

    long long ans=(solve(st2,len2)%mod+mod-solve(st1,len1)%mod)%mod;
    printf("%lld\n",ans);
//    solve(st2,len2);
    /*
    for(int i=1;i<=len2;i++) {
        for(int j=0;j<=4;j++) {
            if(dp[i][j]!=-1) 
                cout<<i<<' '<<j<<' '<<dp[i][j]<<endl;
        }
    }
    */
//   cout<<endl<<solve(st2,len2)<<endl;
    return 0;
}